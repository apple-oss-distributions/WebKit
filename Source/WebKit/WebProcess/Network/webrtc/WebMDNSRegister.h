/*
 * Copyright (C) 2018 Apple Inc. All rights reserved.
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

#if ENABLE(WEB_RTC)

#include "MDNSRegisterIdentifier.h"
#include <WebCore/DocumentIdentifier.h>
#include <WebCore/LibWebRTCProvider.h>
#include <wtf/Expected.h>
#include <wtf/Forward.h>
#include <wtf/HashMap.h>

namespace IPC {
class Connection;
class Decoder;
}

namespace WebKit {

class WebMDNSRegister {
public:
    WebMDNSRegister() = default;

    void unregisterMDNSNames(WebCore::DocumentIdentifier);
    void registerMDNSName(WebCore::DocumentIdentifier, const String& ipAddress, CompletionHandler<void(WebCore::LibWebRTCProvider::MDNSNameOrError&&)>&&);

    void didReceiveMessage(IPC::Connection&, IPC::Decoder&);

private:
    void finishedRegisteringMDNSName(MDNSRegisterIdentifier, WebCore::LibWebRTCProvider::MDNSNameOrError&&);

    struct PendingRegistration {
        CompletionHandler<void(WebCore::LibWebRTCProvider::MDNSNameOrError&&)> callback;
        WebCore::DocumentIdentifier documentIdentifier;
        String ipAddress;
    };
    HashMap<MDNSRegisterIdentifier, PendingRegistration> m_pendingRegistrations;

    HashMap<WebCore::DocumentIdentifier, HashMap<String, String>> m_registeringDocuments;
};

} // namespace WebKit

#endif // ENABLE(WEB_RTC)