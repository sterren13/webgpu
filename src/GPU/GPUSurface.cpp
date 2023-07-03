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
#define PLATFORM PLATFORM_WAYLAND
#if PLATFORM == PLATFORM_WAYLAND
#define GLFW_EXPOSE_NATIVE_WAYLAND
#elif PLATFORM == PLATFORM_X11
#define GLFW_EXPOSE_NATIVE_X11
#endif
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
#if PLATFORM == PLATFORM_WAYLAND
    struct wl_display* wayland_display = glfwGetWaylandDisplay();
    struct wl_surface* wayland_surface = glfwGetWaylandWindow(w.m_Window);
    WGPUChainedStruct chain{
            .next = nullptr,
            .sType = WGPUSType_SurfaceDescriptorFromWaylandSurface,
    };
    WGPUSurfaceDescriptorFromWaylandSurface surfaceDescriptorFromWaylandSurface{
            .chain = chain,
            .display = wayland_display,
            .surface = wayland_surface,
    };

    WGPUSurfaceDescriptor surfaceDescriptor{
            .nextInChain = (const WGPUChainedStruct*)(&surfaceDescriptorFromWaylandSurface),
            .label = nullptr
    };
    surface = wgpuInstanceCreateSurface(instance.m_instance, &surfaceDescriptor);
#elif PLATFORM == PLATFORM_X11
    Display* x11_display = glfwGetX11Display();
    Window x11_window = glfwGetX11Window(w.m_Window);
    WGPUChainedStruct chain{
            .next = nullptr,
            .sType = WGPUSType_SurfaceDescriptorFromXlibWindow,
    };
    WGPUSurfaceDescriptorFromXlibWindow surfaceDescriptorFromXlibWindow{
        .chain = chain,
        .display = x11_display,
        .window = static_cast<uint32_t>(x11_window),
    };

    WGPUSurfaceDescriptor surfaceDescriptor{
            .nextInChain = (const WGPUChainedStruct*)(&surfaceDescriptorFromXlibWindow),
            .label = nullptr
    };
    surface = wgpuInstanceCreateSurface(instance.m_instance, &surfaceDescriptor);
#endif
#endif

}

GPUSurface::~GPUSurface() {

}