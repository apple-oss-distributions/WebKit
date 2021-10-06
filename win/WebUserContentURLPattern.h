/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WebUserContentURLPattern_h
#define WebUserContentURLPattern_h

#include <WebCore/COMPtr.h>
#include <WebCore/UserContentURLPattern.h>

namespace WebCore {
    class UserContentURLPattern;
}

class WebUserContentURLPattern : public Noncopyable, public IWebUserContentURLPattern {
public:
    static COMPtr<WebUserContentURLPattern> createInstance();

    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();

private:
    WebUserContentURLPattern();
    ~WebUserContentURLPattern();

    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, void** ppvObject);
    virtual HRESULT STDMETHODCALLTYPE parse(BSTR patternString);
    virtual HRESULT STDMETHODCALLTYPE isValid(BOOL*);
    virtual HRESULT STDMETHODCALLTYPE scheme(BSTR*);
    virtual HRESULT STDMETHODCALLTYPE host(BSTR*);
    virtual HRESULT STDMETHODCALLTYPE matchesSubdomains(BOOL* matches);
    virtual HRESULT STDMETHODCALLTYPE matchesURL(BSTR, BOOL*);

    ULONG m_refCount;
    WebCore::UserContentURLPattern m_pattern;
};

#endif // WebScriptWorld_h
