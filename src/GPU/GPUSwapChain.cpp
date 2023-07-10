//
// Created by sterr on 5/07/2023.
//

#include "GPUSwapChain.h"

GPUSwapChain::GPUSwapChain(GPUSurface& surface, GPUAdapter& adapter, GPUDevice& device) {
    swapChainDesc = {
            .width = 640,
            .height = 480,
            .presentMode = WGPUPresentMode_Fifo
    };
    swapChainFormat = wgpuSurfaceGetPreferredFormat(surface.surface, adapter.adapter);
    swapChainDesc.usage = WGPUTextureUsage_RenderAttachment;
    swapChainDesc.format = swapChainFormat;

    swapChain = wgpuDeviceCreateSwapChain(device.device, surface.surface, &swapChainDesc);
}

GPUSwapChain::~GPUSwapChain() {
    wgpuSwapChainRelease(swapChain);
}

WGPUTextureView GPUSwapChain::CurrentTextureView() {
    return wgpuSwapChainGetCurrentTextureView(swapChain);
}

void GPUSwapChain::Present() {
    wgpuSwapChainPresent(swapChain);
}
