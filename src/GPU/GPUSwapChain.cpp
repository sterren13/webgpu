//
// Created by sterr on 3/07/2023.
//

#include "GPUSwapChain.h"
#include "webgpu/wgpu.h"

GPUSwapChain::GPUSwapChain(GPUDevice& device ,GPUAdapter& adapter, GPUSurface& surface) {
    WGPUSwapChainDescriptor swapChainDescriptor = {};
    swapChainDescriptor.width = 640;
    swapChainDescriptor.height = 480;
    swapChainDescriptor.usage = WGPUTextureUsage_RenderAttachment;

    WGPUTextureFormat swapChainFormat = wgpuSurfaceGetPreferredFormat(surface.surface, adapter.adapter);
    swapChainDescriptor.format = swapChainFormat;
    swapChainDescriptor.presentMode = WGPUPresentMode_Fifo;

    swapChain = wgpuDeviceCreateSwapChain(device.device, surface.surface, &swapChainDescriptor);
}

GPUSwapChain::~GPUSwapChain() {
    wgpuSwapChainDrop(swapChain);
}

WGPUTextureView GPUSwapChain::GetCurrentView() {
    return wgpuSwapChainGetCurrentTextureView(swapChain);
}

void GPUSwapChain::Present() {
    wgpuSwapChainPresent(swapChain);
}

void GPUSwapChain::ReleaseView(WGPUTextureView view) {
    wgpuTextureViewDrop(view);
}
