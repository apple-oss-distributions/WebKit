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
#include "CrossOriginEmbedderPolicy.h"

#include "HTTPHeaderNames.h"
#include "HTTPParsers.h"
#include "JSFetchRequest.h"
#include "PingLoader.h"
#include "ResourceResponse.h"
#include "ScriptExecutionContext.h"
#include "SecurityOrigin.h"

namespace WebCore {

static URL contextURLForReport(Frame& frame)
{
    auto reportURL = frame.document() ? frame.document()->url() : aboutBlankURL();
    if (reportURL.isAboutBlank()) {
        if (auto* parentFrame = frame.tree().parent(); parentFrame->document())
            reportURL = parentFrame->document()->url();
        else if (auto* openerFrame = frame.loader().opener(); openerFrame->document())
            reportURL = openerFrame->document()->url();
    }
    return reportURL;
}

// https://html.spec.whatwg.org/multipage/origin.html#obtain-an-embedder-policy
CrossOriginEmbedderPolicy obtainCrossOriginEmbedderPolicy(const ResourceResponse& response, const ScriptExecutionContext* context)
{
    auto parseCOEPHeader = [&response](HTTPHeaderName headerName, auto& value, auto& reportingEndpoint) {
        auto coepParsingResult = parseStructuredFieldValue(response.httpHeaderField(headerName));
        if (coepParsingResult && coepParsingResult->first == "require-corp") {
            value = CrossOriginEmbedderPolicyValue::RequireCORP;
            reportingEndpoint = coepParsingResult->second.get("report-to"_s);
        }
    };

    CrossOriginEmbedderPolicy policy;
    if (context && !context->settingsValues().crossOriginEmbedderPolicyEnabled)
        return policy;
    if (!SecurityOrigin::create(response.url())->isPotentiallyTrustworthy())
        return policy;

    parseCOEPHeader(HTTPHeaderName::CrossOriginEmbedderPolicy, policy.value, policy.reportingEndpoint);
    parseCOEPHeader(HTTPHeaderName::CrossOriginEmbedderPolicyReportOnly, policy.reportOnlyValue, policy.reportOnlyReportingEndpoint);
    return policy;
}

CrossOriginEmbedderPolicy CrossOriginEmbedderPolicy::isolatedCopy() const
{
    return {
        value,
        reportingEndpoint.isolatedCopy(),
        reportOnlyValue,
        reportOnlyReportingEndpoint.isolatedCopy()
    };
}

void addCrossOriginEmbedderPolicyHeaders(ResourceResponse& response, const CrossOriginEmbedderPolicy& coep)
{
    if (coep.value != CrossOriginEmbedderPolicyValue::UnsafeNone) {
        ASSERT(coep.value == CrossOriginEmbedderPolicyValue::RequireCORP);
        if (coep.reportingEndpoint.isEmpty())
            response.setHTTPHeaderField(HTTPHeaderName::CrossOriginEmbedderPolicy, "require-corp"_s);
        else
            response.setHTTPHeaderField(HTTPHeaderName::CrossOriginEmbedderPolicy, makeString("require-corp; report-to=\"", coep.reportingEndpoint, '\"'));
    }
    if (coep.reportOnlyValue != CrossOriginEmbedderPolicyValue::UnsafeNone) {
        ASSERT(coep.reportOnlyValue == CrossOriginEmbedderPolicyValue::RequireCORP);
        if (coep.reportOnlyReportingEndpoint.isEmpty())
            response.setHTTPHeaderField(HTTPHeaderName::CrossOriginEmbedderPolicyReportOnly, "require-corp"_s);
        else
            response.setHTTPHeaderField(HTTPHeaderName::CrossOriginEmbedderPolicyReportOnly, makeString("require-corp; report-to=\"", coep.reportOnlyReportingEndpoint, '\"'));
    }
}

// https://html.spec.whatwg.org/multipage/origin.html#queue-a-cross-origin-embedder-policy-inheritance-violation
void sendCOEPPolicyInheritenceViolation(Frame& frame, const WebCore::SecurityOriginData& embedderOrigin, const String& endpoint, COEPDisposition disposition, const String& type, const URL& blockedURL)
{
    if (!frame.settings().coopCoepViolationReportingEnabled())
        return;

    ASSERT(!endpoint.isEmpty());
    PingLoader::sendReportToEndpoint(frame, embedderOrigin, endpoint, "coep"_s, contextURLForReport(frame), frame.loader().userAgent(blockedURL), [&](auto& body) {
        body.setString("disposition"_s, disposition == COEPDisposition::Reporting ? "reporting"_s : "enforce"_s);
        body.setString("type"_s, type);
        body.setString("blockedURL"_s, PingLoader::sanitizeURLForReport(blockedURL));
    });
}

// https://fetch.spec.whatwg.org/#queue-a-cross-origin-embedder-policy-corp-violation-report
void sendCOEPCORPViolation(Frame& frame, const SecurityOriginData& embedderOrigin, const String& endpoint, COEPDisposition disposition, FetchOptions::Destination destination, const URL& blockedURL)
{
    ASSERT(!endpoint.isEmpty());
    if (!frame.settings().coopCoepViolationReportingEnabled())
        return;

    PingLoader::sendReportToEndpoint(frame, embedderOrigin, endpoint, "coep"_s, contextURLForReport(frame), frame.loader().userAgent(blockedURL), [&](auto& body) {
        body.setString("disposition"_s, disposition == COEPDisposition::Reporting ? "reporting"_s : "enforce"_s);
        body.setString("type"_s, "corp");
        body.setString("blockedURL"_s, PingLoader::sanitizeURLForReport(blockedURL));
        body.setString("destination"_s, convertEnumerationToString(destination));
    });
}

} // namespace WebCore
