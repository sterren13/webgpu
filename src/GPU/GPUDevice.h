//
// Created by sterr on 3/07/2023.
//

#ifndef TESTWEBGPU_GPUDEVICE_H
#define TESTWEBGPU_GPUDEVICE_H
#include "GPUAdapter.h"

class GPUDevice {
public:
    GPUDevice(GPUAdapter& adapter);
    ~GPUDevice();

    void inspect();

    static void onDeviceError(WGPUErrorType type, char const* massage, void* pUserData);

public:
    friend class GPUCommandBuffer;
    friend class GPUSwapChain;
    friend class GPUShader;
    friend class GPURenderPipeline;
    friend class GPUBuffer;

    WGPUDevice device;
    WGPUDeviceDescriptor descriptor;
    WGPURequiredLimits requiredLimits{};
};


#endif //TESTWEBGPU_GPUDEVICE_H
