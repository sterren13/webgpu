//
// Created by sterr on 2/07/2023.
//

#ifndef TESTWEBGPU_GPUINSTANCE_H
#define TESTWEBGPU_GPUINSTANCE_H
#include "webgpu/webgpu.h"


// TODO chose api backend

enum class GPU_Backend{
    WGPUBackendType_Null = 0x00000000,
    WGPUBackendType_WebGPU = 0x00000001,
    WGPUBackendType_D3D11 = 0x00000002,
    WGPUBackendType_D3D12 = 0x00000003,
    WGPUBackendType_Metal = 0x00000004,
    WGPUBackendType_Vulkan = 0x00000005,
    WGPUBackendType_OpenGL = 0x00000006,
    WGPUBackendType_OpenGLES = 0x00000007,
    WGPUBackendType_Force32 = 0x7FFFFFFF
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
