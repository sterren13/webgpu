//
// Created by sterr on 3/07/2023.
//

#ifndef TESTWEBGPU_GPUSWAPCHAIN_H
#define TESTWEBGPU_GPUSWAPCHAIN_H
#include <webgpu/webgpu.h>
#include "GPUAdapter.h"
#include "GPUInstance.h"
#include "GPUDevice.h"

class GPUSwapChain {
public:
    GPUSwapChain(GPUDevice& device ,GPUAdapter& adapter, GPUSurface& surface);
    ~GPUSwapChain();

    WGPUTextureView GetCurrentView();
    void ReleaseView(WGPUTextureView view);
    void Present();

private:
    WGPUSwapChain swapChain = nullptr;
    WGPUSwapChainDescriptor swapChainDescriptor;
};


#endif //TESTWEBGPU_GPUSWAPCHAIN_H
