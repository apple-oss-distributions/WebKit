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
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
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
#import <WebCore/WebCoreObjCExtras.h>
#import <objc/objc-auto.h>
#import <runtime/InitializeThreading.h>

BOOL applicationIsTerminating = NO;
int pluginDatabaseClientCount = 0;

@implementation WebViewPrivate

+ (void)initialize
{
    JSC::initializeThreading();
#ifndef BUILDING_ON_TIGER
    WebCoreObjCFinalizeOnMainThread(self);
#endif
}

- (id)init 
{
    self = [super init];
    if (!self)
        return nil;

    allowsUndo = YES;
    usesPageCache = YES;
    shouldUpdateWhileOffscreen = YES;
    cssAnimationsSuspended = NO;

    zoomMultiplier = 1;

#if ENABLE(DASHBOARD_SUPPORT)
    dashboardBehaviorAllowWheelScrolling = YES;
#endif

    shouldCloseWithWindow = objc_collecting_enabled();

    smartInsertDeleteEnabled = ![[NSUserDefaults standardUserDefaults] objectForKey:WebSmartInsertDeleteEnabled]
        || [[NSUserDefaults standardUserDefaults] boolForKey:WebSmartInsertDeleteEnabled];


    pluginDatabaseClientCount++;

    return self;
}

- (void)dealloc
{    
    ASSERT(applicationIsTerminating || !page);
    ASSERT(applicationIsTerminating || !preferences);
    ASSERT(!insertionPasteboard);

    [applicationNameForUserAgent release];
    [backgroundColor release];
    [inspector release];
    [currentNodeHighlight release];
    [hostWindow release];
    [policyDelegateForwarder release];
    [UIDelegateForwarder release];
    [frameLoadDelegateForwarder release];
    [editingDelegateForwarder release];
    [mediaStyle release];

    [super dealloc];
}

- (void)finalize
{
    ASSERT_MAIN_THREAD();
    ASSERT(!insertionPasteboard);

    [super finalize];
}

@end
