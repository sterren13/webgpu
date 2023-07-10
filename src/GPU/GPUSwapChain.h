//
// Created by sterr on 5/07/2023.
//

#ifndef TESTWEBGPU_GPUSWAPCHAIN_H
#define TESTWEBGPU_GPUSWAPCHAIN_H
#include <webgpu/webgpu.h>
#include "GPUSurface.h"
#include "GPUAdapter.h"
#include "GPUDevice.h"

class GPUSwapChain {
public:
    GPUSwapChain(GPUSurface& surface, GPUAdapter& adapter, GPUDevice& device);
    ~GPUSwapChain();
    WGPUTextureView CurrentTextureView();
    void Present();
    WGPUTextureFormat swapChainFormat;
private:
    WGPUSwapChainDescriptor swapChainDesc = {};
    WGPUSwapChain swapChain = nullptr;
};


#endif //TESTWEBGPU_GPUSWAPCHAIN_H
