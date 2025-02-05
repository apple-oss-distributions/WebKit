/*
 * Copyright (C) 2024 Apple Inc. All rights reserved.
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

#include "CSSColorConversion+Normalize.h"
#include "CSSColorDescriptors.h"

namespace WebCore {

// This file implements support for converting "raw" parsed values
// (e.g. tuple of `std::variant<NumberRaw, PercentageRaw>`) into typed
// colors (e.g. `SRGBA<float>`).

template<typename Descriptor> GetColorType<Descriptor> normalizeRawComponents(CSSColorParseType<Descriptor>);

template<typename Descriptor, unsigned Index> float normalizeComponent(NumberRaw number)
{
    constexpr auto info = std::get<Index>(Descriptor::components);
    constexpr auto multiplier = info.numberMultiplier;
    constexpr auto min = info.min * info.numberMultiplier;
    constexpr auto max = info.max * info.numberMultiplier;

    if constexpr (info.type == ColorComponentType::Angle)
        return normalizeHue(number.value);
    else if constexpr (info.min == -std::numeric_limits<double>::infinity() && info.max == std::numeric_limits<double>::infinity())
        return number.value * multiplier;
    else if constexpr (info.min == -std::numeric_limits<double>::infinity())
        return std::min(number.value * multiplier, max);
    else if constexpr (info.max == std::numeric_limits<double>::infinity())
        return std::max(number.value * multiplier, min);
    else
        return std::clamp(number.value * multiplier, min, max);
}

template<typename Descriptor, unsigned Index> float normalizeComponent(PercentageRaw percent)
{
    constexpr auto info = std::get<Index>(Descriptor::components);
    constexpr auto multiplier = info.percentMultiplier * info.numberMultiplier;
    constexpr auto min = info.min * info.numberMultiplier;
    constexpr auto max = info.max * info.numberMultiplier;

    if constexpr (info.min == -std::numeric_limits<double>::infinity() && info.max == std::numeric_limits<double>::infinity())
        return percent.value * multiplier;
    else if constexpr (info.min == -std::numeric_limits<double>::infinity())
        return std::min(percent.value * multiplier, max);
    else if constexpr (info.max == std::numeric_limits<double>::infinity())
        return std::max(percent.value * multiplier, min);
    else
        return std::clamp(percent.value * multiplier, min, max);
}

template<typename Descriptor, unsigned Index> float normalizeComponent(AngleRaw angle)
{
    constexpr auto info = std::get<Index>(Descriptor::components);
    static_assert(info.type == ColorComponentType::Angle);

    return normalizeHue(CSSPrimitiveValue::computeDegrees(angle.type, angle.value));
}

template<typename Descriptor, unsigned Index> float normalizeComponent(NoneRaw)
{
    return std::numeric_limits<double>::quiet_NaN();
}

template<typename Descriptor, unsigned Index, typename... Ts> float normalizeComponent(const std::variant<Ts...>& variant)
{
    return WTF::switchOn(variant, [](auto value) { return normalizeComponent<Descriptor, Index>(value); });
}

template<typename Descriptor, unsigned Index, typename T> float normalizeComponent(const std::optional<T>& optional, float defaultValue)
{
    return optional ? normalizeComponent<Descriptor, Index>(*optional) : defaultValue;
}

template<typename Descriptor> GetColorType<Descriptor> convertToTypedColor(CSSColorParseType<Descriptor> parsed, double defaultAlpha)
{
    return {
        normalizeComponent<Descriptor, 0>(std::get<0>(parsed)),
        normalizeComponent<Descriptor, 1>(std::get<1>(parsed)),
        normalizeComponent<Descriptor, 2>(std::get<2>(parsed)),
        normalizeComponent<Descriptor, 3>(std::get<3>(parsed), defaultAlpha)
    };
}

} // namespace WebCore
