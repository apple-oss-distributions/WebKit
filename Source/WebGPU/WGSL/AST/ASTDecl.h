/*
 * Copyright (C) 2022 Apple Inc. All rights reserved.
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

#include "ASTNode.h"

#include <wtf/TypeCasts.h>
#include <wtf/UniqueRefVector.h>

namespace WGSL::AST {

class Decl : public Node {
    WTF_MAKE_FAST_ALLOCATED;

public:
    using List = UniqueRefVector<Decl>;

    Decl(SourceSpan span)
        : Node(span)
    {
    }
};

} // namespace WGSL::AST

SPECIALIZE_TYPE_TRAITS_BEGIN(WGSL::AST::Decl)
static bool isType(const WGSL::AST::Node& node)
{
    switch (node.kind()) {
    case WGSL::AST::Node::Kind::FunctionDecl:
    case WGSL::AST::Node::Kind::StructDecl:
    case WGSL::AST::Node::Kind::VariableDecl:
        return true;
    default:
        return false;
    }
}
SPECIALIZE_TYPE_TRAITS_END()