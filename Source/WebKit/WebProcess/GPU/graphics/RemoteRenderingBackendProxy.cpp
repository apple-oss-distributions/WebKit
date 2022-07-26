/*
 * Copyright (C) 2020-2022 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "RemoteRenderingBackendProxy.h"

#if ENABLE(GPU_PROCESS)

#include "GPUConnectionToWebProcess.h"
#include "Logging.h"
#include "PlatformRemoteImageBufferProxy.h"
#include "RemoteRenderingBackendMessages.h"
#include "RemoteRenderingBackendProxyMessages.h"
#include "WebCoreArgumentCoders.h"
#include "WebPage.h"
#include "WebProcess.h"
#include <JavaScriptCore/TypedArrayInlines.h>

namespace WebKit {

using namespace WebCore;

std::unique_ptr<RemoteRenderingBackendProxy> RemoteRenderingBackendProxy::create(WebPage& webPage)
{
    return std::unique_ptr<RemoteRenderingBackendProxy>(new RemoteRenderingBackendProxy(webPage));
}

RemoteRenderingBackendProxy::RemoteRenderingBackendProxy(WebPage& webPage)
    : m_parameters {
        RenderingBackendIdentifier::generate(),
        webPage.webPageProxyIdentifier(),
        webPage.identifier()
    }
{
}

RemoteRenderingBackendProxy::~RemoteRenderingBackendProxy()
{
    if (!m_gpuProcessConnection)
        return;
    m_gpuProcessConnection->connection().send(Messages::GPUConnectionToWebProcess::ReleaseRenderingBackend(renderingBackendIdentifier()), 0, IPC::SendOption::DispatchMessageEvenWhenWaitingForSyncReply);
    disconnectGPUProcess();
}

GPUProcessConnection& RemoteRenderingBackendProxy::ensureGPUProcessConnection()
{
    if (!m_gpuProcessConnection) {
        m_gpuProcessConnection = &WebProcess::singleton().ensureGPUProcessConnection();
        m_gpuProcessConnection->addClient(*this);

        static constexpr auto connectionBufferSize = 1 << 21;
        auto [streamConnection, dedicatedConnectionClientIdentifer] = IPC::StreamClientConnection::createWithDedicatedConnection(*this, connectionBufferSize);
        m_streamConnection = WTFMove(streamConnection);
        m_streamConnection->open();
        m_gpuProcessConnection->connection().send(Messages::GPUConnectionToWebProcess::CreateRenderingBackend(m_parameters, dedicatedConnectionClientIdentifer, m_streamConnection->streamBuffer()), 0, IPC::SendOption::DispatchMessageEvenWhenWaitingForSyncReply);
    }
    return *m_gpuProcessConnection;
}

void RemoteRenderingBackendProxy::gpuProcessConnectionDidClose(GPUProcessConnection&)
{
    if (!m_gpuProcessConnection)
        return;
    disconnectGPUProcess();
    // Note: The cache will call back to this to setup a new connection.
    m_remoteResourceCacheProxy.remoteResourceCacheWasDestroyed();
}

void RemoteRenderingBackendProxy::disconnectGPUProcess()
{
    m_gpuProcessConnection->removeClient(*this);
    m_gpuProcessConnection->messageReceiverMap().removeMessageReceiver(*this);
    m_gpuProcessConnection = nullptr;

    if (m_destroyGetPixelBufferSharedMemoryTimer.isActive())
        m_destroyGetPixelBufferSharedMemoryTimer.stop();
    m_getPixelBufferSharedMemory = nullptr;
    m_renderingUpdateID = { };
    m_didRenderingUpdateID = { };
    m_streamConnection->invalidate();
    m_streamConnection = nullptr;
}

RemoteRenderingBackendProxy::DidReceiveBackendCreationResult RemoteRenderingBackendProxy::waitForDidCreateImageBufferBackend()
{
    if (!streamConnection().waitForAndDispatchImmediately<Messages::RemoteRenderingBackendProxy::DidCreateImageBufferBackend>(renderingBackendIdentifier(), 1_s, IPC::WaitForOption::InterruptWaitingIfSyncMessageArrives))
        return DidReceiveBackendCreationResult::TimeoutOrIPCFailure;
    return DidReceiveBackendCreationResult::ReceivedAnyResponse;
}

bool RemoteRenderingBackendProxy::waitForDidFlush()
{
    return streamConnection().waitForAndDispatchImmediately<Messages::RemoteRenderingBackendProxy::DidFlush>(renderingBackendIdentifier(), 1_s, IPC::WaitForOption::InterruptWaitingIfSyncMessageArrives);
}

void RemoteRenderingBackendProxy::createRemoteImageBuffer(ImageBuffer& imageBuffer)
{
    auto logicalSize = imageBuffer.logicalSize();
    sendToStream(Messages::RemoteRenderingBackend::CreateImageBuffer(logicalSize, imageBuffer.renderingMode(), imageBuffer.resolutionScale(), imageBuffer.colorSpace(), imageBuffer.pixelFormat(), imageBuffer.renderingResourceIdentifier()));
}

RefPtr<ImageBuffer> RemoteRenderingBackendProxy::createImageBuffer(const FloatSize& size, RenderingMode renderingMode, float resolutionScale, const DestinationColorSpace& colorSpace, PixelFormat pixelFormat)
{
    RefPtr<ImageBuffer> imageBuffer;

    if (renderingMode == RenderingMode::Accelerated) {
        // Unless DOM rendering is always enabled when any GPU process rendering is enabled,
        // we need to create ImageBuffers for e.g. Canvas that are actually mapped into the
        // Web Content process, so they can be painted into the tiles.
        if (!WebProcess::singleton().shouldUseRemoteRenderingFor(RenderingPurpose::DOM))
            imageBuffer = AcceleratedRemoteImageBufferMappedProxy::create(size, resolutionScale, colorSpace, pixelFormat, *this);
        else
            imageBuffer = AcceleratedRemoteImageBufferProxy::create(size, resolutionScale, colorSpace, pixelFormat, *this);
    }

    if (!imageBuffer)
        imageBuffer = UnacceleratedRemoteImageBufferProxy::create(size, resolutionScale, colorSpace, pixelFormat, *this);

    if (imageBuffer) {
        createRemoteImageBuffer(*imageBuffer);
        return imageBuffer;
    }

    return nullptr;
}

bool RemoteRenderingBackendProxy::getPixelBufferForImageBuffer(WebCore::RenderingResourceIdentifier imageBuffer, const WebCore::PixelBufferFormat& destinationFormat, const WebCore::IntRect& srcRect, Span<uint8_t> result)
{
    if (auto handle = updateSharedMemoryForGetPixelBuffer(result.size())) {
        SharedMemory::IPCHandle ipcHandle { WTFMove(*handle), m_getPixelBufferSharedMemory->size() };
        auto sendResult = sendSyncToStream(Messages::RemoteRenderingBackend::GetPixelBufferForImageBufferWithNewMemory(imageBuffer, ipcHandle, destinationFormat, srcRect),
            Messages::RemoteRenderingBackend::GetPixelBufferForImageBufferWithNewMemory::Reply());
        if (!sendResult)
            return false;
    } else {
        if (!m_getPixelBufferSharedMemory)
            return false;
        auto sendResult = sendSyncToStream(Messages::RemoteRenderingBackend::GetPixelBufferForImageBuffer(imageBuffer, destinationFormat, srcRect), Messages::RemoteRenderingBackend::GetPixelBufferForImageBuffer::Reply());
        if (!sendResult)
            return false;
    }
    memcpy(result.data(), m_getPixelBufferSharedMemory->data(), result.size());
    return true;
}

void RemoteRenderingBackendProxy::putPixelBufferForImageBuffer(WebCore::RenderingResourceIdentifier imageBuffer, const WebCore::PixelBuffer& pixelBuffer, const WebCore::IntRect& srcRect, const WebCore::IntPoint& destPoint, WebCore::AlphaPremultiplication destFormat)
{
    sendToStream(Messages::RemoteRenderingBackend::PutPixelBufferForImageBuffer(imageBuffer, pixelBuffer, srcRect, destPoint, destFormat));
}

std::optional<SharedMemory::Handle> RemoteRenderingBackendProxy::updateSharedMemoryForGetPixelBuffer(size_t dataSize)
{
    if (m_destroyGetPixelBufferSharedMemoryTimer.isActive())
        m_destroyGetPixelBufferSharedMemoryTimer.stop();

    if (m_getPixelBufferSharedMemory && dataSize <= m_getPixelBufferSharedMemory->size()) {
        m_destroyGetPixelBufferSharedMemoryTimer.startOneShot(5_s);
        return std::nullopt;
    }
    destroyGetPixelBufferSharedMemory();
    auto memory = SharedMemory::allocate(dataSize);
    if (!memory)
        return std::nullopt;
    SharedMemory::Handle handle;
    if (!memory->createHandle(handle, SharedMemory::Protection::ReadWrite))
        return std::nullopt;
    if (handle.isNull())
        return std::nullopt;

    m_getPixelBufferSharedMemory = WTFMove(memory);
    handle.takeOwnershipOfMemory(MemoryLedger::Graphics);
    m_destroyGetPixelBufferSharedMemoryTimer.startOneShot(5_s);
    return handle;
}

void RemoteRenderingBackendProxy::destroyGetPixelBufferSharedMemory()
{
    if (!m_getPixelBufferSharedMemory)
        return;
    m_getPixelBufferSharedMemory = nullptr;
    sendToStream(Messages::RemoteRenderingBackend::DestroyGetPixelBufferSharedMemory());
}

String RemoteRenderingBackendProxy::getDataURLForImageBuffer(const String& mimeType, std::optional<double> quality, PreserveResolution preserveResolution, RenderingResourceIdentifier renderingResourceIdentifier)
{
    String urlString;
    sendSyncToStream(Messages::RemoteRenderingBackend::GetDataURLForImageBuffer(mimeType, quality, preserveResolution, renderingResourceIdentifier), Messages::RemoteRenderingBackend::GetDataURLForImageBuffer::Reply(urlString));
    return urlString;
}

Vector<uint8_t> RemoteRenderingBackendProxy::getDataForImageBuffer(const String& mimeType, std::optional<double> quality, RenderingResourceIdentifier renderingResourceIdentifier)
{
    Vector<uint8_t> data;
    sendSyncToStream(Messages::RemoteRenderingBackend::GetDataForImageBuffer(mimeType, quality, renderingResourceIdentifier), Messages::RemoteRenderingBackend::GetDataForImageBuffer::Reply(data));
    return data;
}

RefPtr<ShareableBitmap> RemoteRenderingBackendProxy::getShareableBitmap(RenderingResourceIdentifier imageBuffer, PreserveResolution preserveResolution)
{
    ShareableBitmap::Handle handle;
    auto sendResult = sendSyncToStream(Messages::RemoteRenderingBackend::GetShareableBitmapForImageBuffer(imageBuffer, preserveResolution), Messages::RemoteRenderingBackend::GetShareableBitmapForImageBuffer::Reply(handle));
    if (handle.isNull())
        return { };
    handle.takeOwnershipOfMemory(MemoryLedger::Graphics);
    ASSERT_UNUSED(sendResult, sendResult);
    return ShareableBitmap::create(handle);
}

RefPtr<Image> RemoteRenderingBackendProxy::getFilteredImage(RenderingResourceIdentifier imageBuffer, Filter& filter)
{
    ShareableBitmap::Handle handle;
    auto sendResult = sendSyncToStream(Messages::RemoteRenderingBackend::GetFilteredImageForImageBuffer(imageBuffer, IPC::FilterReference { filter }), Messages::RemoteRenderingBackend::GetFilteredImageForImageBuffer::Reply(handle));
    ASSERT_UNUSED(sendResult, sendResult);

    if (handle.isNull())
        return { };

    handle.takeOwnershipOfMemory(MemoryLedger::Graphics);
    auto bitmap = ShareableBitmap::create(handle);
    if (!bitmap)
        return { };

    return bitmap->createImage();
}

void RemoteRenderingBackendProxy::cacheNativeImage(const ShareableBitmap::Handle& handle, RenderingResourceIdentifier renderingResourceIdentifier)
{
    sendToStream(Messages::RemoteRenderingBackend::CacheNativeImage(handle, renderingResourceIdentifier));
}

void RemoteRenderingBackendProxy::cacheFont(Ref<Font>&& font)
{
    sendToStream(Messages::RemoteRenderingBackend::CacheFont(WTFMove(font)));
}

void RemoteRenderingBackendProxy::deleteAllFonts()
{
    sendToStream(Messages::RemoteRenderingBackend::DeleteAllFonts());
}

void RemoteRenderingBackendProxy::releaseRemoteResource(RenderingResourceIdentifier renderingResourceIdentifier)
{
    sendToStream(Messages::RemoteRenderingBackend::ReleaseRemoteResource(renderingResourceIdentifier));
}

void RemoteRenderingBackendProxy::finalizeRenderingUpdate()
{
    sendToStream(Messages::RemoteRenderingBackend::FinalizeRenderingUpdate(m_renderingUpdateID));
    m_remoteResourceCacheProxy.finalizeRenderingUpdate();
    m_renderingUpdateID.increment();
}

void RemoteRenderingBackendProxy::didCreateImageBufferBackend(ImageBufferBackendHandle handle, RenderingResourceIdentifier renderingResourceIdentifier)
{
    auto imageBuffer = m_remoteResourceCacheProxy.cachedImageBuffer(renderingResourceIdentifier);
    if (!imageBuffer)
        return;

    if (imageBuffer->renderingMode() == RenderingMode::Unaccelerated)
        imageBuffer->setBackend(UnacceleratedImageBufferShareableBackend::create(imageBuffer->parameters(), WTFMove(handle)));
    else if (imageBuffer->canMapBackingStore())
        imageBuffer->setBackend(AcceleratedImageBufferShareableMappedBackend::create(imageBuffer->parameters(), WTFMove(handle)));
    else
        imageBuffer->setBackend(AcceleratedImageBufferShareableBackend::create(imageBuffer->parameters(), WTFMove(handle)));
}

void RemoteRenderingBackendProxy::didFlush(GraphicsContextFlushIdentifier flushIdentifier, RenderingResourceIdentifier renderingResourceIdentifier)
{
    if (auto imageBuffer = m_remoteResourceCacheProxy.cachedImageBuffer(renderingResourceIdentifier))
        imageBuffer->didFlush(flushIdentifier);
}

void RemoteRenderingBackendProxy::didFinalizeRenderingUpdate(RenderingUpdateID didRenderingUpdateID)
{
    ASSERT(didRenderingUpdateID <= m_renderingUpdateID);
    m_didRenderingUpdateID = std::min(didRenderingUpdateID, m_renderingUpdateID);
}

RenderingBackendIdentifier RemoteRenderingBackendProxy::renderingBackendIdentifier() const
{
    return m_parameters.identifier;
}

RenderingBackendIdentifier RemoteRenderingBackendProxy::ensureBackendCreated()
{
    ensureGPUProcessConnection();
    return renderingBackendIdentifier();
}

IPC::StreamClientConnection& RemoteRenderingBackendProxy::streamConnection()
{
    ensureGPUProcessConnection();
    if (UNLIKELY(!m_streamConnection->hasWakeUpSemaphore()))
        m_streamConnection->waitForAndDispatchImmediately<Messages::RemoteRenderingBackendProxy::DidCreateWakeUpSemaphoreForDisplayListStream>(renderingBackendIdentifier(), 3_s, IPC::WaitForOption::InterruptWaitingIfSyncMessageArrives);
    return *m_streamConnection;
}

void RemoteRenderingBackendProxy::didCreateWakeUpSemaphoreForDisplayListStream(IPC::Semaphore&& semaphore)
{
    if (!m_streamConnection) {
        ASSERT_NOT_REACHED();
        return;
    }
    m_streamConnection->setWakeUpSemaphore(WTFMove(semaphore));
}

bool RemoteRenderingBackendProxy::isCached(const ImageBuffer& imageBuffer) const
{
    if (auto cachedImageBuffer = m_remoteResourceCacheProxy.cachedImageBuffer(imageBuffer.renderingResourceIdentifier())) {
        ASSERT(cachedImageBuffer == &imageBuffer);
        return true;
    }
    return false;
}

} // namespace WebKit

#endif // ENABLE(GPU_PROCESS)
