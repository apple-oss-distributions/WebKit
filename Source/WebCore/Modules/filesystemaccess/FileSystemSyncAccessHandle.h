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

#pragma once

#include "BufferSource.h"
#include "ExceptionOr.h"
#include "FileSystemSyncAccessHandleIdentifier.h"
#include "IDLTypes.h"
#include <wtf/FileSystem.h>
#include <wtf/WeakPtr.h>

namespace WebCore {

class FileSystemFileHandle;
template<typename> class DOMPromiseDeferred;

class FileSystemSyncAccessHandle : public RefCounted<FileSystemSyncAccessHandle>, public CanMakeWeakPtr<FileSystemSyncAccessHandle> {
public:
    struct FilesystemReadWriteOptions {
        unsigned long long at;
    };

    static Ref<FileSystemSyncAccessHandle> create(FileSystemFileHandle&, FileSystemSyncAccessHandleIdentifier, FileSystem::PlatformFileHandle);
    ~FileSystemSyncAccessHandle();

    void truncate(unsigned long long size, DOMPromiseDeferred<void>&&);
    void getSize(DOMPromiseDeferred<IDLUnsignedLongLong>&&);
    void flush(DOMPromiseDeferred<void>&&);
    void close(DOMPromiseDeferred<void>&&);
    void didClose(ExceptionOr<void>&&);
    ExceptionOr<unsigned long long> read(BufferSource&&, FilesystemReadWriteOptions);
    ExceptionOr<unsigned long long> write(BufferSource&&, FilesystemReadWriteOptions);

private:
    FileSystemSyncAccessHandle(FileSystemFileHandle&, FileSystemSyncAccessHandleIdentifier, FileSystem::PlatformFileHandle);
    bool isClosingOrClosed() const;
    void closeInternal(CompletionHandler<void(ExceptionOr<void>&&)>&&);

    Ref<FileSystemFileHandle> m_source;
    FileSystemSyncAccessHandleIdentifier m_identifier;
    uint64_t m_pendingOperationCount { 0 };
    FileSystem::PlatformFileHandle m_file;
    std::optional<ExceptionOr<void>> m_closeResult;
    Vector<DOMPromiseDeferred<void>> m_closePromises;
};

} // namespace WebCore
