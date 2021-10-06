/*
 * Copyright (C) 2006, 2007, 2008 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "WebKitDLL.h"
#include "WebFrame.h"

#include "CFDictionaryPropertyBag.h"
#include "COMPtr.h"
#include "COMPropertyBag.h"
#include "DefaultPolicyDelegate.h"
#include "DOMCoreClasses.h"
#include "HTMLFrameOwnerElement.h"
#include "MarshallingHelpers.h"
#include "WebActionPropertyBag.h"
#include "WebChromeClient.h"
#include "WebDocumentLoader.h"
#include "WebDownload.h"
#include "WebError.h"
#include "WebMutableURLRequest.h"
#include "WebEditorClient.h"
#include "WebFramePolicyListener.h"
#include "WebHistory.h"
#include "WebIconFetcher.h"
#include "WebKit.h"
#include "WebKitStatisticsPrivate.h"
#include "WebNotificationCenter.h"
#include "WebView.h"
#include "WebDataSource.h"
#include "WebHistoryItem.h"
#include "WebURLResponse.h"
#pragma warning( push, 0 )
#include <WebCore/BString.h>
#include <WebCore/Cache.h>
#include <WebCore/Document.h>
#include <WebCore/DocumentLoader.h>
#include <WebCore/DOMImplementation.h>
#include <WebCore/DOMWindow.h>
#include <WebCore/Event.h>
#include <WebCore/EventHandler.h>
#include <WebCore/FormState.h>
#include <WebCore/FrameLoader.h>
#include <WebCore/FrameLoadRequest.h>
#include <WebCore/FrameTree.h>
#include <WebCore/FrameView.h>
#include <WebCore/FrameWin.h>
#include <WebCore/GDIObjectCounter.h>
#include <WebCore/GraphicsContext.h>
#include <WebCore/HistoryItem.h>
#include <WebCore/HTMLAppletElement.h>
#include <WebCore/HTMLFormElement.h>
#include <WebCore/HTMLFormControlElement.h>
#include <WebCore/HTMLInputElement.h>
#include <WebCore/HTMLNames.h>
#include <WebCore/HTMLPlugInElement.h>
#include <WebCore/JSDOMWindow.h>
#include <WebCore/KeyboardEvent.h>
#include <WebCore/MIMETypeRegistry.h>
#include <WebCore/MouseRelatedEvent.h>
#include <WebCore/NotImplemented.h>
#include <WebCore/Page.h>
#include <WebCore/PlatformKeyboardEvent.h>
#include <WebCore/PluginInfoStore.h>
#include <WebCore/PluginDatabase.h>
#include <WebCore/PluginView.h>
#include <WebCore/ResourceHandle.h>
#include <WebCore/ResourceHandleWin.h>
#include <WebCore/ResourceRequest.h>
#include <WebCore/RenderView.h>
#include <WebCore/RenderTreeAsText.h>
#include <WebCore/Settings.h>
#include <WebCore/TextIterator.h>
#include <WebCore/JSDOMBinding.h>
#include <WebCore/ScriptController.h>
#include <JavaScriptCore/APICast.h>
#include <wtf/MathExtras.h>
#pragma warning(pop)

#include <CoreGraphics/CoreGraphics.h>

// CG SPI used for printing
extern "C" {
    CGAffineTransform CGContextGetBaseCTM(CGContextRef c); 
    void CGContextSetBaseCTM(CGContextRef c, CGAffineTransform m); 
}

using namespace WebCore;
using namespace HTMLNames;

#define FLASH_REDRAW 0


// By imaging to a width a little wider than the available pixels,
// thin pages will be scaled down a little, matching the way they
// print in IE and Camino. This lets them use fewer sheets than they
// would otherwise, which is presumably why other browsers do this.
// Wide pages will be scaled down more than this.
const float PrintingMinimumShrinkFactor = 1.25f;

// This number determines how small we are willing to reduce the page content
// in order to accommodate the widest line. If the page would have to be
// reduced smaller to make the widest line fit, we just clip instead (this
// behavior matches MacIE and Mozilla, at least)
const float PrintingMaximumShrinkFactor = 2.0f;

//-----------------------------------------------------------------------------
// Helpers to convert from WebCore to WebKit type
WebFrame* kit(Frame* frame)
{
    if (!frame)
        return 0;

    FrameLoaderClient* frameLoaderClient = frame->loader()->client();
    if (frameLoaderClient)
        return static_cast<WebFrame*>(frameLoaderClient);  // eek, is there a better way than static cast?
    return 0;
}

Frame* core(WebFrame* webFrame)
{
    if (!webFrame)
        return 0;
    return webFrame->impl();
}

// This function is not in WebFrame.h because we don't want to advertise the ability to get a non-const Frame from a const WebFrame
Frame* core(const WebFrame* webFrame)
{
    if (!webFrame)
        return 0;
    return const_cast<WebFrame*>(webFrame)->impl();
}

//-----------------------------------------------------------------------------

static Element *elementFromDOMElement(IDOMElement *element)
{
    if (!element)
        return 0;

    COMPtr<IDOMElementPrivate> elePriv;
    HRESULT hr = element->QueryInterface(IID_IDOMElementPrivate, (void**) &elePriv);
    if (SUCCEEDED(hr)) {
        Element* ele;
        hr = elePriv->coreElement((void**)&ele);
        if (SUCCEEDED(hr))
            return ele;
    }
    return 0;
}

static HTMLFormElement *formElementFromDOMElement(IDOMElement *element)
{
    if (!element)
        return 0;

    IDOMElementPrivate* elePriv;
    HRESULT hr = element->QueryInterface(IID_IDOMElementPrivate, (void**) &elePriv);
    if (SUCCEEDED(hr)) {
        Element* ele;
        hr = elePriv->coreElement((void**)&ele);
        elePriv->Release();
        if (SUCCEEDED(hr) && ele && ele->hasTagName(formTag))
            return static_cast<HTMLFormElement*>(ele);
    }
    return 0;
}

static HTMLInputElement* inputElementFromDOMElement(IDOMElement* element)
{
    if (!element)
        return 0;

    IDOMElementPrivate* elePriv;
    HRESULT hr = element->QueryInterface(IID_IDOMElementPrivate, (void**) &elePriv);
    if (SUCCEEDED(hr)) {
        Element* ele;
        hr = elePriv->coreElement((void**)&ele);
        elePriv->Release();
        if (SUCCEEDED(hr) && ele && ele->hasTagName(inputTag))
            return static_cast<HTMLInputElement*>(ele);
    }
    return 0;
}

// WebFramePrivate ------------------------------------------------------------

class WebFrame::WebFramePrivate {
public:
    WebFramePrivate() 
        : frame(0)
        , webView(0)
        , m_policyFunction(0)
    { 
    }

    ~WebFramePrivate() { }
    FrameView* frameView() { return frame ? frame->view() : 0; }

    Frame* frame;
    WebView* webView;
    FramePolicyFunction m_policyFunction;
    COMPtr<WebFramePolicyListener> m_policyListener;
};

// WebFrame ----------------------------------------------------------------

WebFrame::WebFrame()
    : WebFrameLoaderClient(this)
    , m_refCount(0)
    , d(new WebFrame::WebFramePrivate)
    , m_quickRedirectComing(false)
    , m_inPrintingMode(false)
    , m_pageHeight(0)
{
    WebFrameCount++;
    gClassCount++;
    gClassNameCount.add("WebFrame");
}

WebFrame::~WebFrame()
{
    delete d;
    WebFrameCount--;
    gClassCount--;
    gClassNameCount.remove("WebFrame");
}

WebFrame* WebFrame::createInstance()
{
    WebFrame* instance = new WebFrame();
    instance->AddRef();
    return instance;
}

HRESULT STDMETHODCALLTYPE WebFrame::setAllowsScrolling(
    /* [in] */ BOOL flag)
{
    if (Frame* frame = core(this))
        if (FrameView* view = frame->view())
            view->setCanHaveScrollbars(!!flag);

    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::allowsScrolling(
    /* [retval][out] */ BOOL *flag)
{
    if (flag)
        if (Frame* frame = core(this))
            if (FrameView* view = frame->view())
                *flag = view->canHaveScrollbars();

    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::setIsDisconnected(
    /* [in] */ BOOL flag)
{
    if (Frame* frame = core(this)) {
        frame->setIsDisconnected(flag);
        return S_OK;
    }

    return E_FAIL;
}

HRESULT STDMETHODCALLTYPE WebFrame::setExcludeFromTextSearch(
    /* [in] */ BOOL flag)
{
    if (Frame* frame = core(this)) {
        frame->setExcludeFromTextSearch(flag);
        return S_OK;
    }

    return E_FAIL;
}

HRESULT STDMETHODCALLTYPE WebFrame::paintDocumentRectToContext(
    /* [in] */ RECT rect,
    /* [in] */ OLE_HANDLE deviceContext)
{
    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    FrameView* view = coreFrame->view();
    if (!view)
        return E_FAIL;

    // We can't paint with a layout still pending.
    view->layoutIfNeededRecursive();

    HDC dc = (HDC)(ULONG64)deviceContext;
    GraphicsContext gc(dc);
    gc.setShouldIncludeChildWindows(true);
    gc.save();
    LONG width = rect.right - rect.left;
    LONG height = rect.bottom - rect.top;
    FloatRect dirtyRect;
    dirtyRect.setWidth(width);
    dirtyRect.setHeight(height);
    gc.clip(dirtyRect);
    gc.translate(-rect.left, -rect.top);
    view->paintContents(&gc, rect);
    gc.restore();

    return S_OK;
}

// IUnknown -------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE WebFrame::QueryInterface(REFIID riid, void** ppvObject)
{
    *ppvObject = 0;
    if (IsEqualGUID(riid, __uuidof(WebFrame)))
        *ppvObject = this;
    else if (IsEqualGUID(riid, IID_IUnknown))
        *ppvObject = static_cast<IWebFrame*>(this);
    else if (IsEqualGUID(riid, IID_IWebFrame))
        *ppvObject = static_cast<IWebFrame*>(this);
    else if (IsEqualGUID(riid, IID_IWebFramePrivate))
        *ppvObject = static_cast<IWebFramePrivate*>(this);
    else if (IsEqualGUID(riid, IID_IWebDocumentText))
        *ppvObject = static_cast<IWebDocumentText*>(this);
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULONG STDMETHODCALLTYPE WebFrame::AddRef(void)
{
    return ++m_refCount;
}

ULONG STDMETHODCALLTYPE WebFrame::Release(void)
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}

// IWebFrame -------------------------------------------------------------------

HRESULT STDMETHODCALLTYPE WebFrame::name( 
    /* [retval][out] */ BSTR* frameName)
{
    if (!frameName) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *frameName = 0;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    *frameName = BString(coreFrame->tree()->name()).release();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::webView( 
    /* [retval][out] */ IWebView** view)
{
    *view = 0;
    if (!d->webView)
        return E_FAIL;
    *view = d->webView;
    (*view)->AddRef();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::frameView(
    /* [retval][out] */ IWebFrameView** /*view*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebFrame::DOMDocument( 
    /* [retval][out] */ IDOMDocument** result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = 0;

    if (Frame* coreFrame = core(this))
        if (Document* document = coreFrame->document())
            *result = DOMDocument::createInstance(document);

    return *result ? S_OK : E_FAIL;
}

HRESULT STDMETHODCALLTYPE WebFrame::frameElement( 
    /* [retval][out] */ IDOMHTMLElement** frameElement)
{
    if (!frameElement)
        return E_POINTER;

    *frameElement = 0;
    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    COMPtr<IDOMElement> domElement(AdoptCOM, DOMElement::createInstance(coreFrame->ownerElement()));
    COMPtr<IDOMHTMLElement> htmlElement(Query, domElement);
    if (!htmlElement)
        return E_FAIL;
    return htmlElement.copyRefTo(frameElement);
}

HRESULT STDMETHODCALLTYPE WebFrame::currentForm( 
        /* [retval][out] */ IDOMElement **currentForm)
{
    if (!currentForm) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *currentForm = 0;

    if (Frame* coreFrame = core(this))
        if (HTMLFormElement* formElement = coreFrame->currentForm())
            *currentForm = DOMElement::createInstance(formElement);

    return *currentForm ? S_OK : E_FAIL;
}

JSGlobalContextRef STDMETHODCALLTYPE WebFrame::globalContext()
{
    Frame* coreFrame = core(this);
    if (!coreFrame)
        return 0;

    return toGlobalRef(coreFrame->script()->globalObject()->globalExec());
}

HRESULT STDMETHODCALLTYPE WebFrame::loadRequest( 
    /* [in] */ IWebURLRequest* request)
{
    COMPtr<WebMutableURLRequest> requestImpl;

    HRESULT hr = request->QueryInterface(&requestImpl);
    if (FAILED(hr))
        return hr;
 
    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    coreFrame->loader()->load(requestImpl->resourceRequest(), false);
    return S_OK;
}

void WebFrame::loadData(PassRefPtr<WebCore::SharedBuffer> data, BSTR mimeType, BSTR textEncodingName, BSTR baseURL, BSTR failingURL)
{
    String mimeTypeString(mimeType, SysStringLen(mimeType));
    if (!mimeType)
        mimeTypeString = "text/html";

    String encodingString(textEncodingName, SysStringLen(textEncodingName));

    // FIXME: We should really be using MarshallingHelpers::BSTRToKURL here,
    // but that would turn a null BSTR into a null KURL, and we crash inside of
    // WebCore if we use a null KURL in constructing the ResourceRequest.
    KURL baseKURL = KURL(KURL(), String(baseURL ? baseURL : L"", SysStringLen(baseURL)));

    KURL failingKURL = MarshallingHelpers::BSTRToKURL(failingURL);

    ResourceRequest request(baseKURL);
    SubstituteData substituteData(data, mimeTypeString, encodingString, failingKURL);

    // This method is only called from IWebFrame methods, so don't ASSERT that the Frame pointer isn't null.
    if (Frame* coreFrame = core(this))
        coreFrame->loader()->load(request, substituteData, false);
}


HRESULT STDMETHODCALLTYPE WebFrame::loadData( 
    /* [in] */ IStream* data,
    /* [in] */ BSTR mimeType,
    /* [in] */ BSTR textEncodingName,
    /* [in] */ BSTR url)
{
    RefPtr<SharedBuffer> sharedBuffer = SharedBuffer::create();

    STATSTG stat;
    if (SUCCEEDED(data->Stat(&stat, STATFLAG_NONAME))) {
        if (!stat.cbSize.HighPart && stat.cbSize.LowPart) {
            Vector<char> dataBuffer(stat.cbSize.LowPart);
            ULONG read;
            // FIXME: this does a needless copy, would be better to read right into the SharedBuffer
            // or adopt the Vector or something.
            if (SUCCEEDED(data->Read(dataBuffer.data(), static_cast<ULONG>(dataBuffer.size()), &read)))
                sharedBuffer->append(dataBuffer.data(), static_cast<int>(dataBuffer.size()));
        }
    }

    loadData(sharedBuffer, mimeType, textEncodingName, url, 0);
    return S_OK;
}

void WebFrame::loadHTMLString(BSTR string, BSTR baseURL, BSTR unreachableURL)
{
    RefPtr<SharedBuffer> sharedBuffer = SharedBuffer::create(reinterpret_cast<char*>(string), sizeof(UChar) * SysStringLen(string));
    BString utf16Encoding(TEXT("utf-16"), 6);
    loadData(sharedBuffer.release(), 0, utf16Encoding, baseURL, unreachableURL);
}

HRESULT STDMETHODCALLTYPE WebFrame::loadHTMLString( 
    /* [in] */ BSTR string,
    /* [in] */ BSTR baseURL)
{
    loadHTMLString(string, baseURL, 0);
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::loadAlternateHTMLString( 
    /* [in] */ BSTR str,
    /* [in] */ BSTR baseURL,
    /* [in] */ BSTR unreachableURL)
{
    loadHTMLString(str, baseURL, unreachableURL);
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::loadArchive( 
    /* [in] */ IWebArchive* /*archive*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

static inline WebDataSource *getWebDataSource(DocumentLoader* loader)
{
    return loader ? static_cast<WebDocumentLoader*>(loader)->dataSource() : 0;
}

HRESULT STDMETHODCALLTYPE WebFrame::dataSource( 
    /* [retval][out] */ IWebDataSource** source)
{
    if (!source) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *source = 0;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    WebDataSource* webDataSource = getWebDataSource(coreFrame->loader()->documentLoader());

    *source = webDataSource;

    if (webDataSource)
        webDataSource->AddRef(); 

    return *source ? S_OK : E_FAIL;
}

HRESULT STDMETHODCALLTYPE WebFrame::provisionalDataSource( 
    /* [retval][out] */ IWebDataSource** source)
{
    if (!source) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *source = 0;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    WebDataSource* webDataSource = getWebDataSource(coreFrame->loader()->provisionalDocumentLoader());

    *source = webDataSource;

    if (webDataSource)
        webDataSource->AddRef(); 

    return *source ? S_OK : E_FAIL;
}

KURL WebFrame::url() const
{
    Frame* coreFrame = core(this);
    if (!coreFrame)
        return KURL();

    return coreFrame->loader()->url();
}

HRESULT STDMETHODCALLTYPE WebFrame::stopLoading( void)
{
    if (Frame* coreFrame = core(this))
        coreFrame->loader()->stopAllLoaders();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::reload( void)
{
    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    coreFrame->loader()->reload();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::findFrameNamed( 
    /* [in] */ BSTR name,
    /* [retval][out] */ IWebFrame** frame)
{
    if (!frame) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *frame = 0;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    Frame* foundFrame = coreFrame->tree()->find(AtomicString(name, SysStringLen(name)));
    if (!foundFrame)
        return S_OK;

    WebFrame* foundWebFrame = kit(foundFrame);
    if (!foundWebFrame)
        return E_FAIL;

    return foundWebFrame->QueryInterface(IID_IWebFrame, (void**)frame);
}

HRESULT STDMETHODCALLTYPE WebFrame::parentFrame( 
    /* [retval][out] */ IWebFrame** frame)
{
    HRESULT hr = S_OK;
    *frame = 0;
    if (Frame* coreFrame = core(this))
        if (WebFrame* webFrame = kit(coreFrame->tree()->parent()))
            hr = webFrame->QueryInterface(IID_IWebFrame, (void**) frame);

    return hr;
}

class EnumChildFrames : public IEnumVARIANT
{
public:
    EnumChildFrames(Frame* f) : m_refCount(1), m_frame(f), m_curChild(f ? f->tree()->firstChild() : 0) { }

    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject)
    {
        *ppvObject = 0;
        if (IsEqualGUID(riid, IID_IUnknown) || IsEqualGUID(riid, IID_IEnumVARIANT))
            *ppvObject = this;
        else
            return E_NOINTERFACE;

        AddRef();
        return S_OK;
    }

    virtual ULONG STDMETHODCALLTYPE AddRef(void)
    {
        return ++m_refCount;
    }

    virtual ULONG STDMETHODCALLTYPE Release(void)
    {
        ULONG newRef = --m_refCount;
        if (!newRef)
            delete(this);
        return newRef;
    }

    virtual HRESULT STDMETHODCALLTYPE Next(ULONG celt, VARIANT *rgVar, ULONG *pCeltFetched)
    {
        if (pCeltFetched)
            *pCeltFetched = 0;
        if (!rgVar)
            return E_POINTER;
        VariantInit(rgVar);
        if (!celt || celt > 1)
            return S_FALSE;
        if (!m_frame || !m_curChild)
            return S_FALSE;

        WebFrame* webFrame = kit(m_curChild);
        IUnknown* unknown;
        HRESULT hr = webFrame->QueryInterface(IID_IUnknown, (void**)&unknown);
        if (FAILED(hr))
            return hr;

        V_VT(rgVar) = VT_UNKNOWN;
        V_UNKNOWN(rgVar) = unknown;

        m_curChild = m_curChild->tree()->nextSibling();
        if (pCeltFetched)
            *pCeltFetched = 1;
        return S_OK;
    }

    virtual HRESULT STDMETHODCALLTYPE Skip(ULONG celt)
    {
        if (!m_frame)
            return S_FALSE;
        for (unsigned i = 0; i < celt && m_curChild; i++)
            m_curChild = m_curChild->tree()->nextSibling();
        return m_curChild ? S_OK : S_FALSE;
    }

    virtual HRESULT STDMETHODCALLTYPE Reset(void)
    {
        if (!m_frame)
            return S_FALSE;
        m_curChild = m_frame->tree()->firstChild();
        return S_OK;
    }

    virtual HRESULT STDMETHODCALLTYPE Clone(IEnumVARIANT**)
    {
        return E_NOTIMPL;
    }

private:
    ULONG m_refCount;
    Frame* m_frame;
    Frame* m_curChild;
};

HRESULT STDMETHODCALLTYPE WebFrame::childFrames( 
    /* [retval][out] */ IEnumVARIANT **enumFrames)
{
    if (!enumFrames)
        return E_POINTER;

    *enumFrames = new EnumChildFrames(core(this));
    return S_OK;
}

// IWebFramePrivate ------------------------------------------------------

HRESULT STDMETHODCALLTYPE WebFrame::renderTreeAsExternalRepresentation(
    /* [retval][out] */ BSTR *result)
{
    if (!result)
        return E_POINTER;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    *result = BString(externalRepresentation(coreFrame->contentRenderer())).release();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::scrollOffset(
        /* [retval][out] */ SIZE* offset)
{
    if (!offset) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    FrameView* view = coreFrame->view();
    if (!view)
        return E_FAIL;

    *offset = view->scrollOffset();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::layout()
{
    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    FrameView* view = coreFrame->view();
    if (!view)
        return E_FAIL;

    view->layout();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::firstLayoutDone(
    /* [retval][out] */ BOOL* result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = 0;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    *result = coreFrame->loader()->firstLayoutDone();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::loadType( 
    /* [retval][out] */ WebFrameLoadType* type)
{
    if (!type) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *type = (WebFrameLoadType)0;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    *type = (WebFrameLoadType)coreFrame->loader()->loadType();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::pendingFrameUnloadEventCount( 
    /* [retval][out] */ UINT* result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = 0;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    *result = coreFrame->domWindow()->pendingUnloadEventListeners();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::fetchApplicationIcon( 
    /* [in] */ IWebIconFetcherDelegate *delegate,
    /* [retval][out] */ IWebIconFetcher **result)
{
    if (!result)
        return E_POINTER;

    *result = 0;

    if (!delegate)
        return E_FAIL;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    *result = WebIconFetcher::fetchApplicationIcon(coreFrame, delegate);
    if (!*result)
        return E_FAIL;

    return S_OK;
}

// IWebDocumentText -----------------------------------------------------------

HRESULT STDMETHODCALLTYPE WebFrame::supportsTextEncoding( 
    /* [retval][out] */ BOOL* result)
{
    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebFrame::selectedString( 
    /* [retval][out] */ BSTR* result)
{
    *result = 0;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    String text = coreFrame->displayStringModifiedByEncoding(coreFrame->selectedText());

    *result = BString(text).release();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::selectAll()
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE WebFrame::deselectAll()
{
    return E_NOTIMPL;
}

// WebFrame ---------------------------------------------------------------

PassRefPtr<Frame> WebFrame::init(IWebView* webView, Page* page, HTMLFrameOwnerElement* ownerElement)
{
    webView->QueryInterface(&d->webView);
    d->webView->Release(); // don't hold the extra ref

    HWND viewWindow;
    d->webView->viewWindow((OLE_HANDLE*)&viewWindow);

    this->AddRef(); // We release this ref in frameLoaderDestroyed()
    RefPtr<Frame> frame = Frame::create(page, ownerElement, this);
    d->frame = frame.get();
    return frame.release();
}

Frame* WebFrame::impl()
{
    return d->frame;
}

void WebFrame::invalidate()
{
    Frame* coreFrame = core(this);
    ASSERT(coreFrame);

    if (Document* document = coreFrame->document())
        document->recalcStyle(Node::Force);
}

void WebFrame::setTextSizeMultiplier(float multiplier)
{
    Frame* coreFrame = core(this);
    ASSERT(coreFrame);
    coreFrame->setZoomFactor(multiplier, true);
}

HRESULT WebFrame::inViewSourceMode(BOOL* flag)
{
    if (!flag) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *flag = FALSE;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    *flag = coreFrame->inViewSourceMode() ? TRUE : FALSE;
    return S_OK;
}

HRESULT WebFrame::setInViewSourceMode(BOOL flag)
{
    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    coreFrame->setInViewSourceMode(!!flag);
    return S_OK;
}

HRESULT WebFrame::elementWithName(BSTR name, IDOMElement* form, IDOMElement** element)
{
    if (!form)
        return E_INVALIDARG;

    HTMLFormElement *formElement = formElementFromDOMElement(form);
    if (formElement) {
        Vector<HTMLFormControlElement*>& elements = formElement->formElements;
        AtomicString targetName((UChar*)name, SysStringLen(name));
        for (unsigned int i = 0; i < elements.size(); i++) {
            HTMLFormControlElement *elt = elements[i];
            // Skip option elements, other duds
            if (elt->name() == targetName) {
                *element = DOMElement::createInstance(elt);
                return S_OK;
            }
        }
    }
    return E_FAIL;
}

HRESULT WebFrame::formForElement(IDOMElement* element, IDOMElement** form)
{
    if (!element)
        return E_INVALIDARG;

    HTMLInputElement *inputElement = inputElementFromDOMElement(element);
    if (!inputElement)
        return E_FAIL;

    HTMLFormElement *formElement = inputElement->form();
    if (!formElement)
        return E_FAIL;

    *form = DOMElement::createInstance(formElement);
    return S_OK;
}

HRESULT WebFrame::elementDoesAutoComplete(IDOMElement *element, BOOL *result)
{
    *result = false;
    if (!element)
        return E_INVALIDARG;

    HTMLInputElement *inputElement = inputElementFromDOMElement(element);
    if (!inputElement)
        *result = false;
    else
        *result = (inputElement->inputType() == HTMLInputElement::TEXT && inputElement->autoComplete());

    return S_OK;
}

HRESULT WebFrame::pauseAnimation(BSTR animationName, IDOMNode* node, double secondsFromNow, BOOL* animationWasRunning)
{
    if (!node || !animationWasRunning)
        return E_POINTER;

    *animationWasRunning = FALSE;

    Frame* frame = core(this);
    if (!frame)
        return E_FAIL;

    AnimationController* controller = frame->animation();
    if (!controller)
        return E_FAIL;

    COMPtr<DOMNode> domNode(Query, node);
    if (!domNode)
        return E_FAIL;

    *animationWasRunning = controller->pauseAnimationAtTime(domNode->node()->renderer(), String(animationName, SysStringLen(animationName)), secondsFromNow);
    return S_OK;
}

HRESULT WebFrame::pauseTransition(BSTR propertyName, IDOMNode* node, double secondsFromNow, BOOL* transitionWasRunning)
{
    if (!node || !transitionWasRunning)
        return E_POINTER;

    *transitionWasRunning = FALSE;

    Frame* frame = core(this);
    if (!frame)
        return E_FAIL;

    AnimationController* controller = frame->animation();
    if (!controller)
        return E_FAIL;

    COMPtr<DOMNode> domNode(Query, node);
    if (!domNode)
        return E_FAIL;

    *transitionWasRunning = controller->pauseTransitionAtTime(domNode->node()->renderer(), String(propertyName, SysStringLen(propertyName)), secondsFromNow);
    return S_OK;
}

HRESULT WebFrame::numberOfActiveAnimations(UINT* number)
{
    if (!number)
        return E_POINTER;

    *number = 0;

    Frame* frame = core(this);
    if (!frame)
        return E_FAIL;

    AnimationController* controller = frame->animation();
    if (!controller)
        return E_FAIL;

    *number = controller->numberOfActiveAnimations();
    return S_OK;
}

HRESULT WebFrame::isDisplayingStandaloneImage(BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;

    Frame* frame = core(this);
    if (!frame)
        return E_FAIL;

    Document* document = frame->document();
    *result = document && document->isImageDocument();
    return S_OK;
}

HRESULT WebFrame::allowsFollowingLink(BSTR url, BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = TRUE;

    Frame* frame = core(this);
    if (!frame)
        return E_FAIL;

    *result = FrameLoader::canLoad(MarshallingHelpers::BSTRToKURL(url), String(), frame->document());
    return S_OK;
}

HRESULT WebFrame::controlsInForm(IDOMElement* form, IDOMElement** controls, int* cControls)
{
    if (!form)
        return E_INVALIDARG;

    HTMLFormElement *formElement = formElementFromDOMElement(form);
    if (!formElement)
        return E_FAIL;

    int inCount = *cControls;
    int count = (int) formElement->formElements.size();
    *cControls = count;
    if (!controls)
        return S_OK;
    if (inCount < count)
        return E_FAIL;

    *cControls = 0;
    Vector<HTMLFormControlElement*>& elements = formElement->formElements;
    for (int i = 0; i < count; i++) {
        if (elements.at(i)->isEnumeratable()) { // Skip option elements, other duds
            controls[*cControls] = DOMElement::createInstance(elements.at(i));
            (*cControls)++;
        }
    }
    return S_OK;
}

HRESULT WebFrame::elementIsPassword(IDOMElement *element, bool *result)
{
    HTMLInputElement *inputElement = inputElementFromDOMElement(element);
    *result = inputElement != 0
        && inputElement->inputType() == HTMLInputElement::PASSWORD;
    return S_OK;
}

HRESULT WebFrame::searchForLabelsBeforeElement(const BSTR* labels, int cLabels, IDOMElement* beforeElement, BSTR* result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = 0;

    if (!cLabels)
        return S_OK;
    if (cLabels < 1)
        return E_INVALIDARG;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    Vector<String> labelStrings(cLabels);
    for (int i=0; i<cLabels; i++)
        labelStrings[i] = String(labels[i], SysStringLen(labels[i]));
    Element *coreElement = elementFromDOMElement(beforeElement);
    if (!coreElement)
        return E_FAIL;

    String label = coreFrame->searchForLabelsBeforeElement(labelStrings, coreElement);
    
    *result = SysAllocStringLen(label.characters(), label.length());
    if (label.length() && !*result)
        return E_OUTOFMEMORY;
    return S_OK;
}

HRESULT WebFrame::matchLabelsAgainstElement(const BSTR* labels, int cLabels, IDOMElement* againstElement, BSTR* result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = 0;

    if (!cLabels)
        return S_OK;
    if (cLabels < 1)
        return E_INVALIDARG;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    Vector<String> labelStrings(cLabels);
    for (int i=0; i<cLabels; i++)
        labelStrings[i] = String(labels[i], SysStringLen(labels[i]));
    Element *coreElement = elementFromDOMElement(againstElement);
    if (!coreElement)
        return E_FAIL;

    String label = coreFrame->matchLabelsAgainstElement(labelStrings, coreElement);
    
    *result = SysAllocStringLen(label.characters(), label.length());
    if (label.length() && !*result)
        return E_OUTOFMEMORY;
    return S_OK;
}

HRESULT WebFrame::canProvideDocumentSource(bool* result)
{
    HRESULT hr = S_OK;
    *result = false;

    COMPtr<IWebDataSource> dataSource;
    hr = WebFrame::dataSource(&dataSource);
    if (FAILED(hr))
        return hr;

    COMPtr<IWebURLResponse> urlResponse;
    hr = dataSource->response(&urlResponse);
    if (SUCCEEDED(hr) && urlResponse) {
        BSTR mimeTypeBStr;
        if (SUCCEEDED(urlResponse->MIMEType(&mimeTypeBStr))) {
            String mimeType(mimeTypeBStr, SysStringLen(mimeTypeBStr));
            *result = mimeType == "text/html" || WebCore::DOMImplementation::isXMLMIMEType(mimeType);
            SysFreeString(mimeTypeBStr);
        }
    }
    return hr;
}

void WebFrame::frameLoaderDestroyed()
{
    // The FrameLoader going away is equivalent to the Frame going away,
    // so we now need to clear our frame pointer.
    d->frame = 0;

    this->Release();
}

void WebFrame::makeRepresentation(DocumentLoader*)
{
    notImplemented();
}

void WebFrame::forceLayoutForNonHTML()
{
    notImplemented();
}

void WebFrame::setCopiesOnScroll()
{
    notImplemented();
}

void WebFrame::detachedFromParent2()
{
    notImplemented();
}

void WebFrame::detachedFromParent3()
{
    notImplemented();
}

void WebFrame::cancelPolicyCheck()
{
    if (d->m_policyListener) {
        d->m_policyListener->invalidate();
        d->m_policyListener = 0;
    }

    d->m_policyFunction = 0;
}

void WebFrame::dispatchWillSubmitForm(FramePolicyFunction function, PassRefPtr<FormState> formState)
{
    Frame* coreFrame = core(this);
    ASSERT(coreFrame);

    COMPtr<IWebFormDelegate> formDelegate;

    if (FAILED(d->webView->formDelegate(&formDelegate))) {
        (coreFrame->loader()->*function)(PolicyUse);
        return;
    }

    COMPtr<IDOMElement> formElement(AdoptCOM, DOMElement::createInstance(formState->form()));

    HashMap<String, String> formValuesMap;
    const StringPairVector& textFieldValues = formState->textFieldValues();
    size_t size = textFieldValues.size();
    for (size_t i = 0; i < size; ++i)
        formValuesMap.add(textFieldValues[i].first, textFieldValues[i].second);

    COMPtr<IPropertyBag> formValuesPropertyBag(AdoptCOM, COMPropertyBag<String>::createInstance(formValuesMap));

    COMPtr<WebFrame> sourceFrame(kit(formState->sourceFrame()));
    if (SUCCEEDED(formDelegate->willSubmitForm(this, sourceFrame.get(), formElement.get(), formValuesPropertyBag.get(), setUpPolicyListener(function).get())))
        return;

    // FIXME: Add a sane default implementation
    (coreFrame->loader()->*function)(PolicyUse);
}

void WebFrame::revertToProvisionalState(DocumentLoader*)
{
    notImplemented();
}

void WebFrame::setMainFrameDocumentReady(bool)
{
    notImplemented();
}

void WebFrame::willChangeTitle(DocumentLoader*)
{
    notImplemented();
}

void WebFrame::didChangeTitle(DocumentLoader*)
{
    notImplemented();
}

bool WebFrame::canHandleRequest(const ResourceRequest& request) const
{
    return WebView::canHandleRequest(request);
}

bool WebFrame::canShowMIMEType(const String& /*MIMEType*/) const
{
    notImplemented();
    return true;
}

bool WebFrame::representationExistsForURLScheme(const String& /*URLScheme*/) const
{
    notImplemented();
    return false;
}

String WebFrame::generatedMIMETypeForURLScheme(const String& /*URLScheme*/) const
{
    notImplemented();
    ASSERT_NOT_REACHED();
    return String();
}

void WebFrame::frameLoadCompleted()
{
}

void WebFrame::restoreViewState()
{
}

void WebFrame::provisionalLoadStarted()
{
    notImplemented();
}

bool WebFrame::shouldTreatURLAsSameAsCurrent(const KURL&) const
{
    notImplemented();
    return false;
}

void WebFrame::addHistoryItemForFragmentScroll()
{
    notImplemented();
}

void WebFrame::didFinishLoad()
{
    notImplemented();
}

void WebFrame::prepareForDataSourceReplacement()
{
    notImplemented();
}

String WebFrame::userAgent(const KURL& url)
{
    return d->webView->userAgentForKURL(url);
}

void WebFrame::saveViewStateToItem(HistoryItem*)
{
}

ResourceError WebFrame::cancelledError(const ResourceRequest& request)
{
    // FIXME: Need ChickenCat to include CFNetwork/CFURLError.h to get these values
    // Alternatively, we could create our own error domain/codes.
    return ResourceError(String(WebURLErrorDomain), -999, request.url().string(), String());
}

ResourceError WebFrame::blockedError(const ResourceRequest& request)
{
    // FIXME: Need to implement the String descriptions for errors in the WebKitErrorDomain and have them localized
    return ResourceError(String(WebKitErrorDomain), WebKitErrorCannotUseRestrictedPort, request.url().string(), String());
}

ResourceError WebFrame::cannotShowURLError(const ResourceRequest& request)
{
    // FIXME: Need to implement the String descriptions for errors in the WebKitErrorDomain and have them localized
    return ResourceError(String(WebKitErrorDomain), WebKitErrorCannotShowURL, request.url().string(), String());
}

ResourceError WebFrame::interruptForPolicyChangeError(const ResourceRequest& request)
{
    // FIXME: Need to implement the String descriptions for errors in the WebKitErrorDomain and have them localized
    return ResourceError(String(WebKitErrorDomain), WebKitErrorFrameLoadInterruptedByPolicyChange, request.url().string(), String());
}

ResourceError WebFrame::cannotShowMIMETypeError(const ResourceResponse&)
{
    notImplemented();
    return ResourceError();
}

ResourceError WebFrame::fileDoesNotExistError(const ResourceResponse&)
{
    notImplemented();
    return ResourceError();
}

ResourceError WebFrame::pluginWillHandleLoadError(const ResourceResponse& response)
{
    return ResourceError(String(WebKitErrorDomain), WebKitErrorPlugInWillHandleLoad, response.url().string(), String());
}

bool WebFrame::shouldFallBack(const ResourceError& error)
{
    return error.errorCode() != WebURLErrorCancelled;
}

COMPtr<WebFramePolicyListener> WebFrame::setUpPolicyListener(WebCore::FramePolicyFunction function)
{
    // FIXME: <rdar://5634381> We need to support multiple active policy listeners.

    if (d->m_policyListener)
        d->m_policyListener->invalidate();

    Frame* coreFrame = core(this);
    ASSERT(coreFrame);

    d->m_policyListener.adoptRef(WebFramePolicyListener::createInstance(coreFrame));
    d->m_policyFunction = function;

    return d->m_policyListener;
}

void WebFrame::receivedPolicyDecision(PolicyAction action)
{
    ASSERT(d->m_policyListener);
    ASSERT(d->m_policyFunction);

    FramePolicyFunction function = d->m_policyFunction;

    d->m_policyListener = 0;
    d->m_policyFunction = 0;

    Frame* coreFrame = core(this);
    ASSERT(coreFrame);

    (coreFrame->loader()->*function)(action);
}

void WebFrame::dispatchDecidePolicyForMIMEType(FramePolicyFunction function, const String& mimeType, const ResourceRequest& request)
{
    Frame* coreFrame = core(this);
    ASSERT(coreFrame);

    COMPtr<IWebPolicyDelegate> policyDelegate;
    if (FAILED(d->webView->policyDelegate(&policyDelegate)))
        policyDelegate = DefaultPolicyDelegate::sharedInstance();

    COMPtr<IWebURLRequest> urlRequest(AdoptCOM, WebMutableURLRequest::createInstance(request));

    if (SUCCEEDED(policyDelegate->decidePolicyForMIMEType(d->webView, BString(mimeType), urlRequest.get(), this, setUpPolicyListener(function).get())))
        return;

    (coreFrame->loader()->*function)(PolicyUse);
}

void WebFrame::dispatchDecidePolicyForNewWindowAction(FramePolicyFunction function, const NavigationAction& action, const ResourceRequest& request, PassRefPtr<FormState> formState, const String& frameName)
{
    Frame* coreFrame = core(this);
    ASSERT(coreFrame);

    COMPtr<IWebPolicyDelegate> policyDelegate;
    if (FAILED(d->webView->policyDelegate(&policyDelegate)))
        policyDelegate = DefaultPolicyDelegate::sharedInstance();

    COMPtr<IWebURLRequest> urlRequest(AdoptCOM, WebMutableURLRequest::createInstance(request));
    COMPtr<WebActionPropertyBag> actionInformation(AdoptCOM, WebActionPropertyBag::createInstance(action, formState ? formState->form() : 0, coreFrame));

    if (SUCCEEDED(policyDelegate->decidePolicyForNewWindowAction(d->webView, actionInformation.get(), urlRequest.get(), BString(frameName), setUpPolicyListener(function).get())))
        return;

    (coreFrame->loader()->*function)(PolicyUse);
}

void WebFrame::dispatchDecidePolicyForNavigationAction(FramePolicyFunction function, const NavigationAction& action, const ResourceRequest& request, PassRefPtr<FormState> formState)
{
    Frame* coreFrame = core(this);
    ASSERT(coreFrame);

    COMPtr<IWebPolicyDelegate> policyDelegate;
    if (FAILED(d->webView->policyDelegate(&policyDelegate)))
        policyDelegate = DefaultPolicyDelegate::sharedInstance();

    COMPtr<IWebURLRequest> urlRequest(AdoptCOM, WebMutableURLRequest::createInstance(request));
    COMPtr<WebActionPropertyBag> actionInformation(AdoptCOM, WebActionPropertyBag::createInstance(action, formState ? formState->form() : 0, coreFrame));

    if (SUCCEEDED(policyDelegate->decidePolicyForNavigationAction(d->webView, actionInformation.get(), urlRequest.get(), this, setUpPolicyListener(function).get())))
        return;

    (coreFrame->loader()->*function)(PolicyUse);
}

void WebFrame::dispatchUnableToImplementPolicy(const ResourceError& error)
{
    COMPtr<IWebPolicyDelegate> policyDelegate;
    if (FAILED(d->webView->policyDelegate(&policyDelegate)))
        policyDelegate = DefaultPolicyDelegate::sharedInstance();

    COMPtr<IWebError> webError(AdoptCOM, WebError::createInstance(error));
    policyDelegate->unableToImplementPolicyWithError(d->webView, webError.get(), this);
}

void WebFrame::download(ResourceHandle* handle, const ResourceRequest& request, const ResourceRequest&, const ResourceResponse& response)
{
    COMPtr<IWebDownloadDelegate> downloadDelegate;
    COMPtr<IWebView> webView;
    if (SUCCEEDED(this->webView(&webView))) {
        if (FAILED(webView->downloadDelegate(&downloadDelegate))) {
            // If the WebView doesn't successfully provide a download delegate we'll pass a null one
            // into the WebDownload - which may or may not decide to use a DefaultDownloadDelegate
            LOG_ERROR("Failed to get downloadDelegate from WebView");
            downloadDelegate = 0;
        }
    }

    // Its the delegate's job to ref the WebDownload to keep it alive - otherwise it will be destroyed
    // when this method returns
    COMPtr<WebDownload> download;
    download.adoptRef(WebDownload::createInstance(handle, request, response, downloadDelegate.get()));
}

bool WebFrame::dispatchDidLoadResourceFromMemoryCache(DocumentLoader*, const ResourceRequest&, const ResourceResponse&, int /*length*/)
{
    notImplemented();
    return false;
}

void WebFrame::dispatchDidFailProvisionalLoad(const ResourceError& error)
{
    COMPtr<IWebFrameLoadDelegate> frameLoadDelegate;
    if (SUCCEEDED(d->webView->frameLoadDelegate(&frameLoadDelegate))) {
        COMPtr<IWebError> webError;
        webError.adoptRef(WebError::createInstance(error));
        frameLoadDelegate->didFailProvisionalLoadWithError(d->webView, webError.get(), this);
    }
}

void WebFrame::dispatchDidFailLoad(const ResourceError& error)
{
    COMPtr<IWebFrameLoadDelegate> frameLoadDelegate;
    if (SUCCEEDED(d->webView->frameLoadDelegate(&frameLoadDelegate))) {
        COMPtr<IWebError> webError;
        webError.adoptRef(WebError::createInstance(error));
        frameLoadDelegate->didFailLoadWithError(d->webView, webError.get(), this);
    }
}

void WebFrame::startDownload(const ResourceRequest& request)
{
    d->webView->downloadURL(request.url());
}

PassRefPtr<Widget> WebFrame::createJavaAppletWidget(const IntSize& pluginSize, HTMLAppletElement* element, const KURL& /*baseURL*/, const Vector<String>& paramNames, const Vector<String>& paramValues)
{
    RefPtr<PluginView> pluginView = PluginView::create(core(this), pluginSize, element, KURL(), paramNames, paramValues, "application/x-java-applet", false);

    // Check if the plugin can be loaded successfully
    if (pluginView->plugin() && pluginView->plugin()->load())
        return pluginView;

    COMPtr<IWebResourceLoadDelegate> resourceLoadDelegate;
    if (FAILED(d->webView->resourceLoadDelegate(&resourceLoadDelegate)))
        return pluginView;

    COMPtr<CFDictionaryPropertyBag> userInfoBag(AdoptCOM, CFDictionaryPropertyBag::createInstance());

    ResourceError resourceError(String(WebKitErrorDomain), WebKitErrorJavaUnavailable, String(), String());
    COMPtr<IWebError> error(AdoptCOM, WebError::createInstance(resourceError, userInfoBag.get()));
     
    resourceLoadDelegate->plugInFailedWithError(d->webView, error.get(), getWebDataSource(d->frame->loader()->documentLoader()));

    return pluginView;
}

ObjectContentType WebFrame::objectContentType(const KURL& url, const String& mimeTypeIn)
{
    String mimeType = mimeTypeIn;
    if (mimeType.isEmpty())
        mimeType = MIMETypeRegistry::getMIMETypeForExtension(url.path().substring(url.path().reverseFind('.') + 1));

    if (mimeType.isEmpty())
        return ObjectContentFrame; // Go ahead and hope that we can display the content.

    if (MIMETypeRegistry::isSupportedImageMIMEType(mimeType))
        return WebCore::ObjectContentImage;

    if (PluginDatabase::installedPlugins()->isMIMETypeRegistered(mimeType))
        return WebCore::ObjectContentNetscapePlugin;

    if (MIMETypeRegistry::isSupportedNonImageMIMEType(mimeType))
        return WebCore::ObjectContentFrame;

    return WebCore::ObjectContentNone;
}

String WebFrame::overrideMediaType() const
{
    notImplemented();
    return String();
}

void WebFrame::windowObjectCleared()
{
    Frame* coreFrame = core(this);
    ASSERT(coreFrame);

    Settings* settings = coreFrame->settings();
    if (!settings || !settings->isJavaScriptEnabled())
        return;

    COMPtr<IWebFrameLoadDelegate> frameLoadDelegate;
    if (SUCCEEDED(d->webView->frameLoadDelegate(&frameLoadDelegate))) {
        JSContextRef context = toRef(coreFrame->script()->globalObject()->globalExec());
        JSObjectRef windowObject = toRef(coreFrame->script()->globalObject());
        ASSERT(windowObject);

        if (FAILED(frameLoadDelegate->didClearWindowObject(d->webView, context, windowObject, this)))
            frameLoadDelegate->windowScriptObjectAvailable(d->webView, context, windowObject);
    }
}

void WebFrame::documentElementAvailable()
{
}

void WebFrame::didPerformFirstNavigation() const
{
    COMPtr<IWebPreferences> preferences;
    if (FAILED(d->webView->preferences(&preferences)))
        return;

    COMPtr<IWebPreferencesPrivate> preferencesPrivate(Query, preferences);
    if (!preferencesPrivate)
        return;
    BOOL automaticallyDetectsCacheModel;
    if (FAILED(preferencesPrivate->automaticallyDetectsCacheModel(&automaticallyDetectsCacheModel)))
        return;

    WebCacheModel cacheModel;
    if (FAILED(preferences->cacheModel(&cacheModel)))
        return;

    if (automaticallyDetectsCacheModel && cacheModel < WebCacheModelDocumentBrowser)
        preferences->setCacheModel(WebCacheModelDocumentBrowser);
}

void WebFrame::registerForIconNotification(bool listen)
{
    d->webView->registerForIconNotification(listen);
}

static IntRect printerRect(HDC printDC)
{
    return IntRect(0, 0, 
                   GetDeviceCaps(printDC, PHYSICALWIDTH)  - 2 * GetDeviceCaps(printDC, PHYSICALOFFSETX),
                   GetDeviceCaps(printDC, PHYSICALHEIGHT) - 2 * GetDeviceCaps(printDC, PHYSICALOFFSETY));
}

void WebFrame::setPrinting(bool printing, float minPageWidth, float maxPageWidth, bool adjustViewSize)
{
    Frame* coreFrame = core(this);
    ASSERT(coreFrame);
    coreFrame->setPrinting(printing, minPageWidth, maxPageWidth, adjustViewSize);
}

HRESULT STDMETHODCALLTYPE WebFrame::setInPrintingMode( 
    /* [in] */ BOOL value,
    /* [in] */ HDC printDC)
{
    if (m_inPrintingMode == !!value)
        return S_OK;

    Frame* coreFrame = core(this);
    if (!coreFrame || !coreFrame->document())
        return E_FAIL;

    m_inPrintingMode = !!value;

    // If we are a frameset just print with the layout we have onscreen, otherwise relayout
    // according to the paper size
    float minLayoutWidth = 0.0f;
    float maxLayoutWidth = 0.0f;
    if (m_inPrintingMode && !coreFrame->document()->isFrameSet()) {
        if (!printDC) {
            ASSERT_NOT_REACHED();
            return E_POINTER;
        }

        const int desiredHorizontalPixelsPerInch = 72;
        int paperHorizontalPixelsPerInch = ::GetDeviceCaps(printDC, LOGPIXELSX);
        int paperWidth = printerRect(printDC).width() * desiredHorizontalPixelsPerInch / paperHorizontalPixelsPerInch;
        minLayoutWidth = paperWidth * PrintingMinimumShrinkFactor;
        maxLayoutWidth = paperWidth * PrintingMaximumShrinkFactor;
    }

    setPrinting(m_inPrintingMode, minLayoutWidth, maxLayoutWidth, true);

    if (!m_inPrintingMode)
        m_pageRects.clear();

    return S_OK;
}

void WebFrame::headerAndFooterHeights(float* headerHeight, float* footerHeight)
{
    if (headerHeight)
        *headerHeight = 0;
    if (footerHeight)
        *footerHeight = 0;
    float height = 0;
    COMPtr<IWebUIDelegate> ui;
    if (FAILED(d->webView->uiDelegate(&ui)))
        return;
    if (headerHeight && SUCCEEDED(ui->webViewHeaderHeight(d->webView, &height)))
        *headerHeight = height;
    if (footerHeight && SUCCEEDED(ui->webViewFooterHeight(d->webView, &height)))
        *footerHeight = height;
}

IntRect WebFrame::printerMarginRect(HDC printDC)
{
    IntRect emptyRect(0, 0, 0, 0);

    COMPtr<IWebUIDelegate> ui;
    if (FAILED(d->webView->uiDelegate(&ui)))
        return emptyRect;

    RECT rect;
    if (FAILED(ui->webViewPrintingMarginRect(d->webView, &rect)))
        return emptyRect;

    rect.left = MulDiv(rect.left, ::GetDeviceCaps(printDC, LOGPIXELSX), 1000);
    rect.top = MulDiv(rect.top, ::GetDeviceCaps(printDC, LOGPIXELSY), 1000);
    rect.right = MulDiv(rect.right, ::GetDeviceCaps(printDC, LOGPIXELSX), 1000);
    rect.bottom = MulDiv(rect.bottom, ::GetDeviceCaps(printDC, LOGPIXELSY), 1000);

    return IntRect(rect.left, rect.top, (rect.right - rect.left), rect.bottom - rect.top);
}

const Vector<WebCore::IntRect>& WebFrame::computePageRects(HDC printDC)
{
    ASSERT(m_inPrintingMode);
    
    Frame* coreFrame = core(this);
    ASSERT(coreFrame);
    ASSERT(coreFrame->document());

    if (!printDC)
        return m_pageRects;

    // adjust the page rect by the header and footer
    float headerHeight = 0, footerHeight = 0;
    headerAndFooterHeights(&headerHeight, &footerHeight);
    IntRect pageRect = printerRect(printDC);
    IntRect marginRect = printerMarginRect(printDC);
    IntRect adjustedRect = IntRect(
        pageRect.x() + marginRect.x(),
        pageRect.y() + marginRect.y(),
        pageRect.width() - marginRect.x() - marginRect.right(),
        pageRect.height() - marginRect.y() - marginRect.bottom());

    computePageRectsForFrame(coreFrame, adjustedRect, headerHeight, footerHeight, 1.0,m_pageRects, m_pageHeight);
    
    return m_pageRects;
}

HRESULT STDMETHODCALLTYPE WebFrame::getPrintedPageCount( 
    /* [in] */ HDC printDC,
    /* [retval][out] */ UINT *pageCount)
{
    if (!pageCount || !printDC) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *pageCount = 0;

    if (!m_inPrintingMode) {
        ASSERT_NOT_REACHED();
        return E_FAIL;
    }

    Frame* coreFrame = core(this);
    if (!coreFrame || !coreFrame->document())
        return E_FAIL;

    const Vector<IntRect>& pages = computePageRects(printDC);
    *pageCount = (UINT) pages.size();
    
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::spoolPages( 
    /* [in] */ HDC printDC,
    /* [in] */ UINT startPage,
    /* [in] */ UINT endPage,
    /* [retval][out] */ void* ctx)
{
    if (!printDC || !ctx) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    if (!m_inPrintingMode) {
        ASSERT_NOT_REACHED();
        return E_FAIL;
    }

    Frame* coreFrame = core(this);
    if (!coreFrame || !coreFrame->document())
        return E_FAIL;

    UINT pageCount = (UINT) m_pageRects.size();
    PlatformGraphicsContext* pctx = (PlatformGraphicsContext*)ctx;

    if (!pageCount || startPage > pageCount) {
        ASSERT_NOT_REACHED();
        return E_FAIL;
    }

    if (startPage > 0)
        startPage--;

    if (endPage == 0)
        endPage = pageCount;

    COMPtr<IWebUIDelegate> ui;
    if (FAILED(d->webView->uiDelegate(&ui)))
        return E_FAIL;

    float headerHeight = 0, footerHeight = 0;
    headerAndFooterHeights(&headerHeight, &footerHeight);
    GraphicsContext spoolCtx(pctx);
    spoolCtx.setShouldIncludeChildWindows(true);

    for (UINT ii = startPage; ii < endPage; ii++) {
        IntRect pageRect = m_pageRects[ii];

        CGContextSaveGState(pctx);

        IntRect printRect = printerRect(printDC);
        CGRect mediaBox = CGRectMake(CGFloat(0),
                                     CGFloat(0),
                                     CGFloat(printRect.width()),
                                     CGFloat(printRect.height()));

        CGContextBeginPage(pctx, &mediaBox);

        CGFloat scale = (float)mediaBox.size.width/ (float)pageRect.width();
        CGAffineTransform ctm = CGContextGetBaseCTM(pctx);
        ctm = CGAffineTransformScale(ctm, -scale, -scale);
        ctm = CGAffineTransformTranslate(ctm, CGFloat(-pageRect.x()), CGFloat(-pageRect.y()+headerHeight)); // reserves space for header
        CGContextScaleCTM(pctx, scale, scale);
        CGContextTranslateCTM(pctx, CGFloat(-pageRect.x()), CGFloat(-pageRect.y()+headerHeight));   // reserves space for header
        CGContextSetBaseCTM(pctx, ctm);

        coreFrame->view()->paintContents(&spoolCtx, pageRect);

        CGContextTranslateCTM(pctx, CGFloat(pageRect.x()), CGFloat(pageRect.y())-headerHeight);

        int x = pageRect.x();
        int y = 0;
        if (headerHeight) {
            RECT headerRect = {x, y, x+pageRect.width(), y+(int)headerHeight};
            ui->drawHeaderInRect(d->webView, &headerRect, (OLE_HANDLE)(LONG64)pctx);
        }

        if (footerHeight) {
            y = max((int)headerHeight+pageRect.height(), m_pageHeight-(int)footerHeight);
            RECT footerRect = {x, y, x+pageRect.width(), y+(int)footerHeight};
            ui->drawFooterInRect(d->webView, &footerRect, (OLE_HANDLE)(LONG64)pctx, ii+1, pageCount);
        }

        CGContextEndPage(pctx);
        CGContextRestoreGState(pctx);
    }
 
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::isFrameSet( 
    /* [retval][out] */ BOOL* result)
{
    *result = FALSE;

    Frame* coreFrame = core(this);
    if (!coreFrame || !coreFrame->document())
        return E_FAIL;

    *result = coreFrame->document()->isFrameSet() ? TRUE : FALSE;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::string( 
    /* [retval][out] */ BSTR *result)
{
    *result = 0;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    RefPtr<Range> allRange(rangeOfContents(coreFrame->document()));
    String allString = plainText(allRange.get());
    *result = BString(allString).release();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::size( 
    /* [retval][out] */ SIZE *size)
{
    if (!size)
        return E_POINTER;
    size->cx = size->cy = 0;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;
    FrameView* view = coreFrame->view();
    if (!view)
        return E_FAIL;
    size->cx = view->width();
    size->cy = view->height();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::hasScrollBars( 
    /* [retval][out] */ BOOL *result)
{
    if (!result)
        return E_POINTER;
    *result = FALSE;

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    FrameView* view = coreFrame->view();
    if (!view)
        return E_FAIL;

    if (view->horizontalScrollbar() || view->verticalScrollbar())
        *result = TRUE;

    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::contentBounds( 
    /* [retval][out] */ RECT *result)
{
    if (!result)
        return E_POINTER;
    ::SetRectEmpty(result);

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    FrameView* view = coreFrame->view();
    if (!view)
        return E_FAIL;

    result->bottom = view->contentsHeight();
    result->right = view->contentsWidth();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::frameBounds( 
    /* [retval][out] */ RECT *result)
{
    if (!result)
        return E_POINTER;
    ::SetRectEmpty(result);

    Frame* coreFrame = core(this);
    if (!coreFrame)
        return E_FAIL;

    FrameView* view = coreFrame->view();
    if (!view)
        return E_FAIL;

    FloatRect bounds = view->visibleContentRect(true);
    result->bottom = (LONG) bounds.height();
    result->right = (LONG) bounds.width();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE WebFrame::isDescendantOfFrame( 
    /* [in] */ IWebFrame *ancestor,
    /* [retval][out] */ BOOL *result)
{
    if (!result)
        return E_POINTER;
    *result = FALSE;

    Frame* coreFrame = core(this);
    COMPtr<WebFrame> ancestorWebFrame(Query, ancestor);
    if (!ancestorWebFrame)
        return S_OK;

    *result = (coreFrame && coreFrame->tree()->isDescendantOf(core(ancestorWebFrame.get()))) ? TRUE : FALSE;
    return S_OK;
}

void WebFrame::unmarkAllMisspellings()
{
    Frame* coreFrame = core(this);
    for (Frame* frame = coreFrame; frame; frame = frame->tree()->traverseNext(coreFrame)) {
        Document *doc = frame->document();
        if (!doc)
            return;

        doc->removeMarkers(DocumentMarker::Spelling);
    }
}

void WebFrame::unmarkAllBadGrammar()
{
    Frame* coreFrame = core(this);
    for (Frame* frame = coreFrame; frame; frame = frame->tree()->traverseNext(coreFrame)) {
        Document *doc = frame->document();
        if (!doc)
            return;

        doc->removeMarkers(DocumentMarker::Grammar);
    }
}

WebView* WebFrame::webView() const
{
    return d->webView;
}

COMPtr<IAccessible> WebFrame::accessible() const
{
    Frame* coreFrame = core(this);
    ASSERT(coreFrame);

    Document* currentDocument = coreFrame->document();
    if (!currentDocument)
        m_accessible = 0;
    else if (!m_accessible || m_accessible->document() != currentDocument) {
        // Either we've never had a wrapper for this frame's top-level Document,
        // the Document renderer was destroyed and its wrapper was detached, or
        // the previous Document is in the page cache, and the current document
        // needs to be wrapped.
        m_accessible = new AccessibleDocument(currentDocument);
    }
    return m_accessible.get();
}

void WebFrame::updateBackground()
{
    Color backgroundColor = webView()->transparent() ? Color::transparent : Color::white;
    Frame* coreFrame = core(this);

    if (!coreFrame || !coreFrame->view())
        return;

    coreFrame->view()->updateBackgroundRecursively(backgroundColor, webView()->transparent());
}

