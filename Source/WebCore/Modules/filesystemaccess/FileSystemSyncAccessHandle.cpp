/*
 * Copyright (C) 2021 Apple Inc. All rights reserved.
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
#include "FileSystemSyncAccessHandle.h"

#include "BufferSource.h"
#include "FileSystemFileHandle.h"
#include "JSDOMPromiseDeferred.h"
#include <wtf/CompletionHandler.h>

namespace WebCore {

Ref<FileSystemSyncAccessHandle> FileSystemSyncAccessHandle::create(FileSystemFileHandle& source, FileSystemSyncAccessHandleIdentifier identifier, FileSystem::PlatformFileHandle file)
{
    return adoptRef(*new FileSystemSyncAccessHandle(source, identifier, file));
}

FileSystemSyncAccessHandle::FileSystemSyncAccessHandle(FileSystemFileHandle& source, FileSystemSyncAccessHandleIdentifier identifier, FileSystem::PlatformFileHandle file)
    : m_source(source)
    , m_identifier(identifier)
    , m_file(file)
{
    ASSERT(m_file != FileSystem::invalidPlatformFileHandle);
}

FileSystemSyncAccessHandle::~FileSystemSyncAccessHandle()
{
    if (m_closeResult)
        return;

    ASSERT(m_closePromises.isEmpty());
    closeInternal([](auto) { });
}

bool FileSystemSyncAccessHandle::isClosingOrClosed() const
{
    return m_closeResult || !m_closePromises.isEmpty();
}

void FileSystemSyncAccessHandle::closeInternal(CompletionHandler<void(ExceptionOr<void>&&)>&& completionHandler)
{
    FileSystem::closeFile(m_file);
    m_source->close(m_identifier, WTFMove(completionHandler));
}

void FileSystemSyncAccessHandle::truncate(unsigned long long size, DOMPromiseDeferred<void>&& promise)
{
    if (isClosingOrClosed())
        return promise.reject(Exception { InvalidStateError, "AccessHandle is closing or closed"_s });

    m_pendingOperationCount++;
    m_source->truncate(m_identifier, size, [weakThis = makeWeakPtr(*this), promise = WTFMove(promise)](auto result) mutable {
        if (weakThis)
            weakThis->m_pendingOperationCount--;

        promise.settle(WTFMove(result));
    });
}

void FileSystemSyncAccessHandle::getSize(DOMPromiseDeferred<IDLUnsignedLongLong>&& promise)
{
    if (isClosingOrClosed())
        return promise.reject(Exception { InvalidStateError, "AccessHandle is closing or closed"_s });

    m_pendingOperationCount++;
    m_source->getSize(m_identifier, [weakThis = makeWeakPtr(*this), promise = WTFMove(promise)](auto result) mutable {
        if (weakThis)
            weakThis->m_pendingOperationCount--;

        promise.settle(WTFMove(result));
    });
}

void FileSystemSyncAccessHandle::flush(DOMPromiseDeferred<void>&& promise)
{
    if (isClosingOrClosed())
        return promise.reject(Exception { InvalidStateError, "AccessHandle is closing or closed"_s });

    m_pendingOperationCount++;
    m_source->flush(m_identifier, [weakThis = makeWeakPtr(*this), promise = WTFMove(promise)](auto result) mutable {
        if (weakThis)
            weakThis->m_pendingOperationCount--;

        promise.settle(WTFMove(result));
    });
}

void FileSystemSyncAccessHandle::close(DOMPromiseDeferred<void>&& promise)
{
    if (m_closeResult)
        return promise.settle(ExceptionOr<void> { *m_closeResult });
    
    auto isClosing = !m_closePromises.isEmpty();
    m_closePromises.append(WTFMove(promise));
    if (isClosing)
        return;

    m_pendingOperationCount++;
    closeInternal([this, protectedThis = Ref { *this }](auto result) mutable {
        m_pendingOperationCount--;
        didClose(WTFMove(result));
    });
}

void FileSystemSyncAccessHandle::didClose(ExceptionOr<void>&& result)
{
    m_closeResult = WTFMove(result);

    auto promises = std::exchange(m_closePromises, { });
    for (auto promise : promises)
        promise.settle(ExceptionOr<void> { *m_closeResult });
}

ExceptionOr<unsigned long long> FileSystemSyncAccessHandle::read(BufferSource&& buffer, FileSystemSyncAccessHandle::FilesystemReadWriteOptions options)
{
    ASSERT(!isMainThread());

    if (isClosingOrClosed())
        return Exception { InvalidStateError, "AccessHandle is closing or closed"_s };

    if (m_pendingOperationCount)
        return Exception { InvalidStateError, "Access handle has unfinished operation"_s };

    int result = FileSystem::seekFile(m_file, options.at, FileSystem::FileSeekOrigin::Beginning);
    if (result == -1)
        return Exception { InvalidStateError, "Failed to read at offset"_s };

    result = FileSystem::readFromFile(m_file, buffer.mutableData(), buffer.length());
    if (result == -1)
        return Exception { InvalidStateError, "Failed to read from file"_s };

    return result;
}

ExceptionOr<unsigned long long> FileSystemSyncAccessHandle::write(BufferSource&& buffer, FileSystemSyncAccessHandle::FilesystemReadWriteOptions options)
{
    ASSERT(!isMainThread());

    if (isClosingOrClosed())
        return Exception { InvalidStateError, "AccessHandle is closing or closed"_s };

    if (m_pendingOperationCount)
        return Exception { InvalidStateError, "Access handle has unfinished operation"_s };

    int result = FileSystem::seekFile(m_file, options.at, FileSystem::FileSeekOrigin::Beginning);
    if (result == -1)
        return Exception { InvalidStateError, "Failed to write at offset"_s };

    result = FileSystem::writeToFile(m_file, buffer.data(), buffer.length());
    if (result == -1)
        return Exception { InvalidStateError, "Failed to write to file"_s };

    return result;
}

} // namespace WebCore
