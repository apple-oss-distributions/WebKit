/*
 * Copyright (C) 2015 Apple Inc. All rights reserved.
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

#import "WebPaymentCoordinatorClient.h"

#if ENABLE(APPLE_PAY)

#import <WebCore/URL.h>
#import <wtf/MainThread.h>

WebPaymentCoordinatorClient::WebPaymentCoordinatorClient()
{
}

WebPaymentCoordinatorClient::~WebPaymentCoordinatorClient()
{
}

bool WebPaymentCoordinatorClient::supportsVersion(unsigned)
{
    return false;
}

bool WebPaymentCoordinatorClient::canMakePayments()
{
    return false;
}

void WebPaymentCoordinatorClient::canMakePaymentsWithActiveCard(const String&, const String&, std::function<void (bool)> completionHandler)
{
    callOnMainThread([completionHandler] {
        completionHandler(false);
    });
}

void WebPaymentCoordinatorClient::openPaymentSetup(const String&, const String&, std::function<void (bool)> completionHandler)
{
    callOnMainThread([completionHandler] {
        completionHandler(false);
    });
}

bool WebPaymentCoordinatorClient::showPaymentUI(const WebCore::URL&, const Vector<WebCore::URL>&, const WebCore::PaymentRequest&)
{
    return false;
}

void WebPaymentCoordinatorClient::completeMerchantValidation(const WebCore::PaymentMerchantSession&)
{
}

void WebPaymentCoordinatorClient::completeShippingMethodSelection(WebCore::PaymentAuthorizationStatus, Optional<WebCore::PaymentRequest::TotalAndLineItems>)
{
}

void WebPaymentCoordinatorClient::completeShippingContactSelection(WebCore::PaymentAuthorizationStatus, const Vector<WebCore::PaymentRequest::ShippingMethod>&, Optional<WebCore::PaymentRequest::TotalAndLineItems>)
{
}

void WebPaymentCoordinatorClient::completePaymentMethodSelection(Optional<WebCore::PaymentRequest::TotalAndLineItems>)
{
}

void WebPaymentCoordinatorClient::completePaymentSession(WebCore::PaymentAuthorizationStatus)
{
}

void WebPaymentCoordinatorClient::abortPaymentSession()
{
}

void WebPaymentCoordinatorClient::paymentCoordinatorDestroyed()
{
    delete this;
}

#endif
