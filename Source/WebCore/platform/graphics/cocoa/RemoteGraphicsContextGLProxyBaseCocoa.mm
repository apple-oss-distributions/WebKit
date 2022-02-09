/*
 * Copyright (C) 2020 Apple Inc.  All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "config.h"
#import "RemoteGraphicsContextGLProxyBase.h"

#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL) && PLATFORM(COCOA)

#import "GraphicsContextGLIOSurfaceSwapChain.h"
#import "WebGLLayer.h"
#import <wtf/BlockObjCExceptions.h>

#if ENABLE(MEDIA_STREAM)
#import "CVUtilities.h"
#import "MediaSampleAVFObjC.h"
#endif

namespace WebCore {

void RemoteGraphicsContextGLProxyBase::platformInitialize()
{
    auto attrs = contextAttributes();
    BEGIN_BLOCK_OBJC_EXCEPTIONS
        m_webGLLayer = adoptNS([[WebGLLayer alloc] initWithDevicePixelRatio:attrs.devicePixelRatio contentsOpaque:!attrs.alpha]);
#ifndef NDEBUG
        [m_webGLLayer setName:@"WebGL Layer"];
#endif
    END_BLOCK_OBJC_EXCEPTIONS
}


PlatformLayer* RemoteGraphicsContextGLProxyBase::platformLayer() const
{
    return m_webGLLayer.get();
}

#if ENABLE(VIDEO) && USE(AVFOUNDATION)
GraphicsContextGLCV* RemoteGraphicsContextGLProxyBase::asCV()
{
    return nullptr;
}
#endif

GraphicsContextGLIOSurfaceSwapChain& RemoteGraphicsContextGLProxyBase::platformSwapChain()
{
    return [m_webGLLayer swapChain];
}

#if ENABLE(MEDIA_STREAM)
RefPtr<MediaSample> RemoteGraphicsContextGLProxyBase::paintCompositedResultsToMediaSample()
{
    auto& sc = platformSwapChain();
    auto& displayBuffer = sc.displayBuffer();
    if (!displayBuffer.surface)
        return nullptr;
    sc.markDisplayBufferInUse();
    auto pixelBuffer = createCVPixelBuffer(displayBuffer.surface->surface());
    if (!pixelBuffer)
        return nullptr;
    return MediaSampleAVFObjC::createImageSample(WTFMove(*pixelBuffer), MediaSampleAVFObjC::VideoRotation::UpsideDown, true);
}
#endif

}
#endif
