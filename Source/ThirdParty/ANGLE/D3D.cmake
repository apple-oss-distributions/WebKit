# This file was generated with the command:
# "./gni-to-cmake.py" "src/libANGLE/renderer/d3d/BUILD.gn" "D3D.cmake" "--prepend" "src/libANGLE/renderer/d3d/"

# Copyright 2020 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# This file houses the build configuration for the ANGLE D3D back-ends.






set(_d3d_shared_sources
    "src/libANGLE/renderer/d3d/BufferD3D.cpp"
    "src/libANGLE/renderer/d3d/BufferD3D.h"
    "src/libANGLE/renderer/d3d/CompilerD3D.cpp"
    "src/libANGLE/renderer/d3d/CompilerD3D.h"
    "src/libANGLE/renderer/d3d/ContextD3D.h"
    "src/libANGLE/renderer/d3d/DeviceD3D.cpp"
    "src/libANGLE/renderer/d3d/DeviceD3D.h"
    "src/libANGLE/renderer/d3d/DisplayD3D.cpp"
    "src/libANGLE/renderer/d3d/DisplayD3D.h"
    "src/libANGLE/renderer/d3d/DynamicHLSL.cpp"
    "src/libANGLE/renderer/d3d/DynamicHLSL.h"
    "src/libANGLE/renderer/d3d/DynamicImage2DHLSL.cpp"
    "src/libANGLE/renderer/d3d/DynamicImage2DHLSL.h"
    "src/libANGLE/renderer/d3d/EGLImageD3D.cpp"
    "src/libANGLE/renderer/d3d/EGLImageD3D.h"
    "src/libANGLE/renderer/d3d/FramebufferD3D.cpp"
    "src/libANGLE/renderer/d3d/FramebufferD3D.h"
    "src/libANGLE/renderer/d3d/HLSLCompiler.cpp"
    "src/libANGLE/renderer/d3d/HLSLCompiler.h"
    "src/libANGLE/renderer/d3d/ImageD3D.cpp"
    "src/libANGLE/renderer/d3d/ImageD3D.h"
    "src/libANGLE/renderer/d3d/IndexBuffer.cpp"
    "src/libANGLE/renderer/d3d/IndexBuffer.h"
    "src/libANGLE/renderer/d3d/IndexDataManager.cpp"
    "src/libANGLE/renderer/d3d/IndexDataManager.h"
    "src/libANGLE/renderer/d3d/NativeWindowD3D.cpp"
    "src/libANGLE/renderer/d3d/NativeWindowD3D.h"
    "src/libANGLE/renderer/d3d/ProgramD3D.cpp"
    "src/libANGLE/renderer/d3d/ProgramD3D.h"
    "src/libANGLE/renderer/d3d/RenderTargetD3D.cpp"
    "src/libANGLE/renderer/d3d/RenderTargetD3D.h"
    "src/libANGLE/renderer/d3d/RenderbufferD3D.cpp"
    "src/libANGLE/renderer/d3d/RenderbufferD3D.h"
    "src/libANGLE/renderer/d3d/RendererD3D.cpp"
    "src/libANGLE/renderer/d3d/RendererD3D.h"
    "src/libANGLE/renderer/d3d/SamplerD3D.h"
    "src/libANGLE/renderer/d3d/ShaderD3D.cpp"
    "src/libANGLE/renderer/d3d/ShaderD3D.h"
    "src/libANGLE/renderer/d3d/ShaderExecutableD3D.cpp"
    "src/libANGLE/renderer/d3d/ShaderExecutableD3D.h"
    "src/libANGLE/renderer/d3d/SurfaceD3D.cpp"
    "src/libANGLE/renderer/d3d/SurfaceD3D.h"
    "src/libANGLE/renderer/d3d/SwapChainD3D.cpp"
    "src/libANGLE/renderer/d3d/SwapChainD3D.h"
    "src/libANGLE/renderer/d3d/TextureD3D.cpp"
    "src/libANGLE/renderer/d3d/TextureD3D.h"
    "src/libANGLE/renderer/d3d/TextureStorage.h"
    "src/libANGLE/renderer/d3d/VertexBuffer.cpp"
    "src/libANGLE/renderer/d3d/VertexBuffer.h"
    "src/libANGLE/renderer/d3d/VertexDataManager.cpp"
    "src/libANGLE/renderer/d3d/VertexDataManager.h"
    "src/libANGLE/renderer/d3d/formatutilsD3D.h"
)


if( NOT angle_is_winuwp)
    list(APPEND _d3d_shared_sources
        "src/libANGLE/renderer/d3d/../../../third_party/systeminfo/SystemInfo.cpp"
        "src/libANGLE/renderer/d3d/../../../third_party/systeminfo/SystemInfo.h"
    )
endif()


if(angle_enable_d3d9)
    set(_d3d9_backend_sources
        "src/libANGLE/renderer/d3d/d3d9/Blit9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/Blit9.h"
        "src/libANGLE/renderer/d3d/d3d9/Buffer9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/Buffer9.h"
        "src/libANGLE/renderer/d3d/d3d9/Context9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/Context9.h"
        "src/libANGLE/renderer/d3d/d3d9/DebugAnnotator9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/DebugAnnotator9.h"
        "src/libANGLE/renderer/d3d/d3d9/Fence9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/Fence9.h"
        "src/libANGLE/renderer/d3d/d3d9/Framebuffer9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/Framebuffer9.h"
        "src/libANGLE/renderer/d3d/d3d9/Image9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/Image9.h"
        "src/libANGLE/renderer/d3d/d3d9/IndexBuffer9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/IndexBuffer9.h"
        "src/libANGLE/renderer/d3d/d3d9/NativeWindow9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/NativeWindow9.h"
        "src/libANGLE/renderer/d3d/d3d9/Query9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/Query9.h"
        "src/libANGLE/renderer/d3d/d3d9/RenderTarget9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/RenderTarget9.h"
        "src/libANGLE/renderer/d3d/d3d9/Renderer9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/Renderer9.h"
        "src/libANGLE/renderer/d3d/d3d9/ShaderCache.h"
        "src/libANGLE/renderer/d3d/d3d9/ShaderExecutable9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/ShaderExecutable9.h"
        "src/libANGLE/renderer/d3d/d3d9/StateManager9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/StateManager9.h"
        "src/libANGLE/renderer/d3d/d3d9/SwapChain9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/SwapChain9.h"
        "src/libANGLE/renderer/d3d/d3d9/TextureStorage9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/TextureStorage9.h"
        "src/libANGLE/renderer/d3d/d3d9/VertexArray9.h"
        "src/libANGLE/renderer/d3d/d3d9/VertexBuffer9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/VertexBuffer9.h"
        "src/libANGLE/renderer/d3d/d3d9/VertexDeclarationCache.cpp"
        "src/libANGLE/renderer/d3d/d3d9/VertexDeclarationCache.h"
        "src/libANGLE/renderer/d3d/d3d9/formatutils9.cpp"
        "src/libANGLE/renderer/d3d/d3d9/formatutils9.h"
        "src/libANGLE/renderer/d3d/d3d9/renderer9_utils.cpp"
        "src/libANGLE/renderer/d3d/d3d9/renderer9_utils.h"
        "src/libANGLE/renderer/d3d/d3d9/shaders/compiled/componentmaskpremultps.h"
        "src/libANGLE/renderer/d3d/d3d9/shaders/compiled/componentmaskps.h"
        "src/libANGLE/renderer/d3d/d3d9/shaders/compiled/componentmaskunmultps.h"
        "src/libANGLE/renderer/d3d/d3d9/shaders/compiled/luminancepremultps.h"
        "src/libANGLE/renderer/d3d/d3d9/shaders/compiled/luminanceps.h"
        "src/libANGLE/renderer/d3d/d3d9/shaders/compiled/luminanceunmultps.h"
        "src/libANGLE/renderer/d3d/d3d9/shaders/compiled/passthroughps.h"
        "src/libANGLE/renderer/d3d/d3d9/shaders/compiled/standardvs.h"
        "src/libANGLE/renderer/d3d/d3d9/vertexconversion.h"
    )
endif()


if(angle_enable_d3d11)
    set(_d3d11_backend_sources
        "src/libANGLE/renderer/d3d/d3d11/Blit11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/Blit11.h"
        "src/libANGLE/renderer/d3d/d3d11/Blit11Helper_autogen.inc"
        "src/libANGLE/renderer/d3d/d3d11/Buffer11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/Buffer11.h"
        "src/libANGLE/renderer/d3d/d3d11/Clear11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/Clear11.h"
        "src/libANGLE/renderer/d3d/d3d11/Context11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/Context11.h"
        "src/libANGLE/renderer/d3d/d3d11/DebugAnnotator11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/DebugAnnotator11.h"
        "src/libANGLE/renderer/d3d/d3d11/ExternalImageSiblingImpl11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/ExternalImageSiblingImpl11.h"
        "src/libANGLE/renderer/d3d/d3d11/Fence11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/Fence11.h"
        "src/libANGLE/renderer/d3d/d3d11/Framebuffer11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/Framebuffer11.h"
        "src/libANGLE/renderer/d3d/d3d11/Image11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/Image11.h"
        "src/libANGLE/renderer/d3d/d3d11/IndexBuffer11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/IndexBuffer11.h"
        "src/libANGLE/renderer/d3d/d3d11/InputLayoutCache.cpp"
        "src/libANGLE/renderer/d3d/d3d11/InputLayoutCache.h"
        "src/libANGLE/renderer/d3d/d3d11/MappedSubresourceVerifier11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/MappedSubresourceVerifier11.h"
        "src/libANGLE/renderer/d3d/d3d11/NativeWindow11.h"
        "src/libANGLE/renderer/d3d/d3d11/PixelTransfer11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/PixelTransfer11.h"
        "src/libANGLE/renderer/d3d/d3d11/Program11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/Program11.h"
        "src/libANGLE/renderer/d3d/d3d11/ProgramPipeline11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/ProgramPipeline11.h"
        "src/libANGLE/renderer/d3d/d3d11/Query11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/Query11.h"
        "src/libANGLE/renderer/d3d/d3d11/RenderStateCache.cpp"
        "src/libANGLE/renderer/d3d/d3d11/RenderStateCache.h"
        "src/libANGLE/renderer/d3d/d3d11/RenderTarget11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/RenderTarget11.h"
        "src/libANGLE/renderer/d3d/d3d11/Renderer11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/Renderer11.h"
        "src/libANGLE/renderer/d3d/d3d11/ResourceManager11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/ResourceManager11.h"
        "src/libANGLE/renderer/d3d/d3d11/ShaderExecutable11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/ShaderExecutable11.h"
        "src/libANGLE/renderer/d3d/d3d11/StateManager11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/StateManager11.h"
        "src/libANGLE/renderer/d3d/d3d11/StreamProducerD3DTexture.cpp"
        "src/libANGLE/renderer/d3d/d3d11/StreamProducerD3DTexture.h"
        "src/libANGLE/renderer/d3d/d3d11/SwapChain11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/SwapChain11.h"
        "src/libANGLE/renderer/d3d/d3d11/TextureStorage11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/TextureStorage11.h"
        "src/libANGLE/renderer/d3d/d3d11/TransformFeedback11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/TransformFeedback11.h"
        "src/libANGLE/renderer/d3d/d3d11/Trim11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/Trim11.h"
        "src/libANGLE/renderer/d3d/d3d11/VertexArray11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/VertexArray11.h"
        "src/libANGLE/renderer/d3d/d3d11/VertexBuffer11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/VertexBuffer11.h"
        "src/libANGLE/renderer/d3d/d3d11/formatutils11.cpp"
        "src/libANGLE/renderer/d3d/d3d11/formatutils11.h"
        "src/libANGLE/renderer/d3d/d3d11/renderer11_utils.cpp"
        "src/libANGLE/renderer/d3d/d3d11/renderer11_utils.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/buffertotexture11_gs.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/buffertotexture11_ps_4f.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/buffertotexture11_ps_4i.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/buffertotexture11_ps_4ui.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/buffertotexture11_vs.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clear11_fl9vs.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clear11multiviewgs.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clear11multiviewvs.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clear11vs.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/cleardepth11ps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearfloat11_fl9ps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearfloat11ps1.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearfloat11ps2.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearfloat11ps3.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearfloat11ps4.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearfloat11ps5.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearfloat11ps6.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearfloat11ps7.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearfloat11ps8.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearsint11ps1.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearsint11ps2.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearsint11ps3.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearsint11ps4.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearsint11ps5.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearsint11ps6.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearsint11ps7.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearsint11ps8.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearuint11ps1.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearuint11ps2.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearuint11ps3.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearuint11ps4.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearuint11ps5.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearuint11ps6.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearuint11ps7.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/clearuint11ps8.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/passthrough2d11vs.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/passthrough3d11gs.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/passthrough3d11vs.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/passthroughdepth2d11ps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/passthroughrgba2dms11ps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/resolvecolor2dps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/resolvedepth11_ps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/resolvedepthstencil11_ps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/resolvedepthstencil11_vs.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/resolvestencil11_ps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/swizzlef2darrayps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/swizzlef2dps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/swizzlef3dps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/swizzlei2darrayps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/swizzlei2dps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/swizzlei3dps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/swizzleui2darrayps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/swizzleui2dps.h"
        "src/libANGLE/renderer/d3d/d3d11/shaders/compiled/swizzleui3dps.h"
        "src/libANGLE/renderer/d3d/d3d11/texture_format_table.cpp"
        "src/libANGLE/renderer/d3d/d3d11/texture_format_table.h"
        "src/libANGLE/renderer/d3d/d3d11/texture_format_table_autogen.cpp"
        "src/libANGLE/renderer/d3d/d3d11/texture_format_table_utils.h"
    )

  
  if(angle_is_winuwp)
        list(APPEND _d3d11_backend_sources
            "src/libANGLE/renderer/d3d/d3d11/winrt/CoreWindowNativeWindow.cpp"
            "src/libANGLE/renderer/d3d/d3d11/winrt/CoreWindowNativeWindow.h"
            "src/libANGLE/renderer/d3d/d3d11/winrt/InspectableNativeWindow.cpp"
            "src/libANGLE/renderer/d3d/d3d11/winrt/InspectableNativeWindow.h"
            "src/libANGLE/renderer/d3d/d3d11/winrt/NativeWindow11WinRT.cpp"
            "src/libANGLE/renderer/d3d/d3d11/winrt/NativeWindow11WinRT.h"
            "src/libANGLE/renderer/d3d/d3d11/winrt/SwapChainPanelNativeWindow.cpp"
            "src/libANGLE/renderer/d3d/d3d11/winrt/SwapChainPanelNativeWindow.h"
        )
    else()
        list(APPEND _d3d11_backend_sources
            "src/libANGLE/renderer/d3d/d3d11/converged/CompositorNativeWindow11.cpp"
            "src/libANGLE/renderer/d3d/d3d11/converged/CompositorNativeWindow11.h"
            "src/libANGLE/renderer/d3d/d3d11/win32/NativeWindow11Win32.cpp"
            "src/libANGLE/renderer/d3d/d3d11/win32/NativeWindow11Win32.h"
        )
    endif()

   set(_d3d11_backend_sources, "${_d3d11_backend_sources};${libangle_d3d11_blit_shaders}")
endif()
