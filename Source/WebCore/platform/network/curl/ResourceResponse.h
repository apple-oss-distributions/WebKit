/*
 * Copyright (C) 2006 Apple Inc.  All rights reserved.
 * Copyright (C) 2018 Sony Interactive Entertainment Inc.
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

#pragma once

#include "ResourceResponseBase.h"

namespace WebCore {

class CurlResponse;

class ResourceResponse : public ResourceResponseBase {
public:
    ResourceResponse()
        : ResourceResponseBase()
    {
    }

    ResourceResponse(const URL& url, const String& mimeType, long long expectedLength, const String& textEncodingName)
        : ResourceResponseBase(url, mimeType, expectedLength, textEncodingName)
    {
    }

    ResourceResponse(ResourceResponseBase&& base)
        : ResourceResponseBase(WTFMove(base))
    {
    }

    WEBCORE_EXPORT ResourceResponse(CurlResponse&);

    bool isMovedPermanently() const { return httpStatusCode() == 301; };
    bool isFound() const { return httpStatusCode() == 302; }
    bool isSeeOther() const { return httpStatusCode() == 303; }
    bool isUnauthorized() const { return httpStatusCode() == 401; }
    bool isProxyAuthenticationRequired() const { return httpStatusCode() == 407; }

private:
    friend class ResourceResponseBase;

    String platformSuggestedFilename() const;

    void appendHTTPHeaderField(const String&);
};

} // namespace WebCore
