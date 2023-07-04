//
// Created by sterr on 1/07/2023.
//

#ifndef TESTWEBGPU_GPUADAPTER_H
#define TESTWEBGPU_GPUADAPTER_H
#include "webgpu/webgpu.h"
#include "GPUSurface.h"
#include "GPUInstance.h"

class GPUAdapter {
public:
    GPUAdapter(GPUInstance& instance, GPUSurface& surface);
    ~GPUAdapter();
    void inspect();

public:
    friend class GPUDevice;
    friend class GPUSwapChain;
    WGPUAdapter adapter;
    WGPURequestAdapterOptions options;
};


#endif //TESTWEBGPU_GPUADAPTER_H
