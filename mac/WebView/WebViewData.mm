/*
 * Copyright (C) 2005, 2006, 2007, 2008, 2009 Apple Inc. All rights reserved.
 * Copyright (C) 2006 David Smith (catfish.man@gmail.com)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution. 
 * 3.  Neither the name of Apple Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "WebViewData.h"

#import "WebKitLogging.h"
#import "WebPreferenceKeysPrivate.h"
#import "WebSelectionServiceController.h"
#import "WebViewGroup.h"
#import <WebCore/AlternativeTextUIController.h>
#import <WebCore/WebCoreObjCExtras.h>
#import <WebCore/HistoryItem.h>
#import <WebCore/TextIndicatorWindow.h>
#import <objc/objc-auto.h>
#import <runtime/InitializeThreading.h>
#import <wtf/MainThread.h>
#import <wtf/RunLoop.h>

#if PLATFORM(IOS)
#import "WebGeolocationProviderIOS.h"
#endif

BOOL applicationIsTerminating = NO;
int pluginDatabaseClientCount = 0;

void LayerFlushController::scheduleLayerFlush()
{
    m_layerFlushScheduler.schedule();
}

void LayerFlushController::invalidate()
{
    m_layerFlushScheduler.invalidate();
    m_webView = nullptr;
}

LayerFlushController::LayerFlushController(WebView* webView)
    : m_webView(webView)
    , m_layerFlushScheduler(this)
{
    ASSERT_ARG(webView, webView);
}

WebViewLayerFlushScheduler::WebViewLayerFlushScheduler(LayerFlushController* flushController)
    : WebCore::LayerFlushScheduler(flushController)
    , m_flushController(flushController)
{
}

@implementation WebViewPrivate

+ (void)initialize
{
#if !PLATFORM(IOS)
    JSC::initializeThreading();
    WTF::initializeMainThreadToProcessMainThread();
    RunLoop::initializeMainRunLoop();
#endif
    WebCoreObjCFinalizeOnMainThread(self);
}

- (id)init 
{
    self = [super init];
    if (!self)
        return nil;

    allowsUndo = YES;
    usesPageCache = YES;
    shouldUpdateWhileOffscreen = YES;

    zoomMultiplier = 1;
    zoomsTextOnly = NO;

    interactiveFormValidationEnabled = NO;
    // The default value should be synchronized with WebCore/page/Settings.cpp.
    validationMessageTimerMagnification = 50;

#if ENABLE(DASHBOARD_SUPPORT)
    dashboardBehaviorAllowWheelScrolling = YES;
#endif

#if PLATFORM(IOS)
    isStopping = NO;
    _geolocationProvider = [WebGeolocationProviderIOS sharedGeolocationProvider];
#endif

#if !PLATFORM(IOS)
    shouldCloseWithWindow = objc_collectingEnabled();
#else
    shouldCloseWithWindow = false;
#endif

    pluginDatabaseClientCount++;

#if USE(DICTATION_ALTERNATIVES)
    m_alternativeTextUIController = adoptPtr(new WebCore::AlternativeTextUIController);
#endif

    return self;
}

- (void)dealloc
{    
    ASSERT(applicationIsTerminating || !page);
    ASSERT(applicationIsTerminating || !preferences);
#if !PLATFORM(IOS)
    ASSERT(!insertionPasteboard);
#endif
#if ENABLE(VIDEO)
    ASSERT(!fullscreenController);
#endif

    [applicationNameForUserAgent release];
#if !PLATFORM(IOS)
    [backgroundColor release];
#else
    CGColorRelease(backgroundColor);
#endif
    [inspector release];
    [currentNodeHighlight release];
#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101000
    [actionMenuController release];
    [immediateActionController release];
#endif
    [hostWindow release];
    [policyDelegateForwarder release];
    [UIDelegateForwarder release];
    [frameLoadDelegateForwarder release];
    [editingDelegateForwarder release];
    [mediaStyle release];

#if ENABLE(REMOTE_INSPECTOR)
#if PLATFORM(IOS)
    [indicateLayer release];
#endif
#endif

#if PLATFORM(IOS)
    [UIKitDelegateForwarder release];
    [formDelegateForwarder release];
    [_caretChangeListeners release];
    [_fixedPositionContent release];
#endif

    [super dealloc];
}

- (void)finalize
{
    ASSERT_MAIN_THREAD();
#if !PLATFORM(IOS)
    ASSERT(!insertionPasteboard);
#endif
#if ENABLE(VIDEO)
    ASSERT(!fullscreenController);
#endif

    [super finalize];
}

@end
