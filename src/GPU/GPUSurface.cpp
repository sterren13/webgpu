//
// Created by sterr on 2/07/2023.
//

#include "GPUSurface.h"
#include "webgpu/webgpu.h"
#include "GLFW/glfw3.h"
#ifdef _WIN64
#define GLFW_EXPOSE_NATIVE_WIN32
#elif _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#elif __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#elif __linux
#define GLFW_EXPOSE_NATIVE_X11
#endif
#include "GLFW/glfw3native.h"


GPUSurface::GPUSurface(GPUInstance& instance, window& w) {
#ifdef _WIN64
    HWND hwnd = glfwGetWin32Window(w.m_Window);
    HINSTANCE  hinstance = GetModuleHandle(NULL);
    WGPUChainedStruct chain{
            .next = nullptr,
            .sType = WGPUSType_SurfaceDescriptorFromWindowsHWND
    };

    WGPUSurfaceDescriptorFromWindowsHWND surfaceDescriptorFromHWND{
            .chain = chain,
            .hinstance = hinstance,
            .hwnd = hwnd
    };

    WGPUSurfaceDescriptor surfaceDescriptor{
            .nextInChain = (const WGPUChainedStruct*)(&surfaceDescriptorFromHWND),
            .label = nullptr
    };
    surface = wgpuInstanceCreateSurface(instance.m_instance, &surfaceDescriptor);
#elif _WIN32
    HWND hwnd = glfwGetWin32Window(w.m_Window);
    HINSTANCE  hinstance = GetModuleHandle(NULL);
    WGPUChainedStruct chain{
            .next = nullptr,
            .sType = WGPUSType_SurfaceDescriptorFromWindowsHWND
    };

    WGPUSurfaceDescriptorFromWindowsHWND surfaceDescriptorFromHWND{
            .chain = chain,
            .hinstance = hinstance,
            .hwnd = hwnd
    };

    WGPUSurfaceDescriptor surfaceDescriptor{
            .nextInChain = (const WGPUChainedStruct*)(&surfaceDescriptorFromHWND),
            .label = nullptr
    };
    surface = wgpuInstanceCreateSurface(instance, &surfaceDescriptor);
#elif __APPLE__

#elif __linux

#endif

}

GPUSurface::~GPUSurface() {

}