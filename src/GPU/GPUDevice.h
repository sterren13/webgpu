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
private:
    friend class GPUCommandBuffer;
    friend class GPUSwapChain;
    WGPUDevice device;
};


#endif //TESTWEBGPU_GPUDEVICE_H
