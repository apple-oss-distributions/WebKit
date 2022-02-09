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
#include "FileSystemStorageManager.h"

#include "FileSystemStorageError.h"

namespace WebKit {

FileSystemStorageManager::FileSystemStorageManager(String&& path, FileSystemStorageHandleRegistry& registry)
    : m_path(WTFMove(path))
    , m_registry(registry)
{
    ASSERT(!RunLoop::isMain());
}

FileSystemStorageManager::~FileSystemStorageManager()
{
    ASSERT(!RunLoop::isMain());

    for (auto identifier : m_handles.keys())
        m_registry.unregisterHandle(identifier);
}

Expected<WebCore::FileSystemHandleIdentifier, FileSystemStorageError> FileSystemStorageManager::createHandle(IPC::Connection::UniqueID connection, FileSystemStorageHandle::Type type, String&& path, String&& name, bool createIfNecessary)
{
    ASSERT(!RunLoop::isMain());

    if (path.isEmpty())
        return makeUnexpected(FileSystemStorageError::Unknown);

    auto fileExists = FileSystem::fileExists(path);
    if (!createIfNecessary && !fileExists)
        return makeUnexpected(FileSystemStorageError::FileNotFound);

    if (fileExists) {
        auto existingFileType = FileSystem::fileType(path);
        if (!existingFileType)
            return makeUnexpected(FileSystemStorageError::Unknown);

        auto existingHandleType = (existingFileType.value() == FileSystem::FileType::Regular) ? FileSystemStorageHandle::Type::File : FileSystemStorageHandle::Type::Directory;
        if (type == FileSystemStorageHandle::Type::Any)
            type = existingHandleType;
        else {
            // Requesting type and existing type should be a match.
            if (existingHandleType != type)
                return makeUnexpected(FileSystemStorageError::TypeMismatch);
        }
    }

    auto newHandle = makeUnique<FileSystemStorageHandle>(*this, type, WTFMove(path), WTFMove(name));
    auto newHandleIdentifier = newHandle->identifier();
    m_handlesByConnection.ensure(connection, [&] {
        return HashSet<WebCore::FileSystemHandleIdentifier> { };
    }).iterator->value.add(newHandleIdentifier);
    m_registry.registerHandle(newHandleIdentifier, *newHandle);
    m_handles.add(newHandleIdentifier, WTFMove(newHandle));
    return newHandleIdentifier;
}

const String& FileSystemStorageManager::getPath(WebCore::FileSystemHandleIdentifier identifier)
{
    auto handle = m_handles.find(identifier);
    return handle == m_handles.end() ? emptyString() : handle->value->path();
}

FileSystemStorageHandle::Type FileSystemStorageManager::getType(WebCore::FileSystemHandleIdentifier identifier)
{
    auto handle = m_handles.find(identifier);
    return handle == m_handles.end() ? FileSystemStorageHandle::Type::Any : handle->value->type();
}

void FileSystemStorageManager::connectionClosed(IPC::Connection::UniqueID connection)
{
    ASSERT(!RunLoop::isMain());

    auto connectionHandles = m_handlesByConnection.find(connection);
    if (connectionHandles == m_handlesByConnection.end())
        return;

    auto identifiers = connectionHandles->value;
    for (auto identifier : identifiers) {
        auto handle = m_handles.take(identifier);
        m_registry.unregisterHandle(identifier);
    }

    m_lockMap.removeIf([&identifiers](auto& entry) {
        return identifiers.contains(entry.value);
    });

    m_handlesByConnection.remove(connectionHandles);
}

Expected<WebCore::FileSystemHandleIdentifier, FileSystemStorageError> FileSystemStorageManager::getDirectory(IPC::Connection::UniqueID connection)
{
    ASSERT(!RunLoop::isMain());

    return createHandle(connection, FileSystemStorageHandle::Type::Directory, String { m_path }, { }, true);
}

bool FileSystemStorageManager::acquireLockForFile(const String& path, WebCore::FileSystemHandleIdentifier identifier)
{
    if (m_lockMap.contains(path))
        return false;

    m_lockMap.add(path, identifier);
    return true;
}

bool FileSystemStorageManager::releaseLockForFile(const String& path, WebCore::FileSystemHandleIdentifier identifier)
{
    if (auto lockedByIdentifier = m_lockMap.get(path); lockedByIdentifier == identifier) {
        m_lockMap.remove(path);
        return true;
    }

    return false;
}

} // namespace WebKit
