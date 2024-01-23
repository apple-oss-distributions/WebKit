/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 * Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies)
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
#include "WebTouchEvent.h"

#if ENABLE(TOUCH_EVENTS) && !PLATFORM(IOS_FAMILY)

#include "WebCoreArgumentCoders.h"

namespace WebKit {

WebPlatformTouchPoint::WebPlatformTouchPoint(unsigned id, State state, const WebCore::IntPoint& screenPosition, const WebCore::IntPoint& position)
    : m_id(id)
    , m_state(state)
    , m_screenPosition(screenPosition)
    , m_position(position)
    , m_rotationAngle(0.0)
    , m_force(0.0)
{
}

WebPlatformTouchPoint::WebPlatformTouchPoint(unsigned id, State state, const WebCore::IntPoint& screenPosition, const WebCore::IntPoint& position, const WebCore::IntSize& radius, float rotationAngle, float force)
    : m_id(id)
    , m_state(state)
    , m_screenPosition(screenPosition)
    , m_position(position)
    , m_radius(radius)
    , m_rotationAngle(rotationAngle)
    , m_force(force)
{
}

} // namespace WebKit

#endif // ENABLE(TOUCH_EVENTS) && !PLATFORM(IOS_FAMILY)
