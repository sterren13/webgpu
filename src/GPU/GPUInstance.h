//
// Created by sterr on 2/07/2023.
//

#ifndef TESTWEBGPU_GPUINSTANCE_H
#define TESTWEBGPU_GPUINSTANCE_H
#include "webgpu/webgpu.h"


// TODO chose api backend

enum class GPU_Backend{
    Empty = 0,
    Vulkan = 1,
    Metal = 2,
    Dx12 = 3,
    Dc11 = 4,
    Gl = 5,
    BrowserWebGpu = 6
};

class GPUInstance {
public:
    GPUInstance();
    ~GPUInstance();
private:
    friend class GPUAdapter;
    friend class GPUSurface;
    WGPUInstance m_instance;
};


#endif //TESTWEBGPU_GPUINSTANCE_H
