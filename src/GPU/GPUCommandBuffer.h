//
// Created by sterr on 3/07/2023.
//

#ifndef TESTWEBGPU_GPUCOMMANDBUFFER_H
#define TESTWEBGPU_GPUCOMMANDBUFFER_H
#include <webgpu/webgpu.h>
#include "GPUDevice.h"
#include "GPURenderPass.h"
#include "GPUTypse.h"

class GPUCommandBuffer {
public:
    GPUCommandBuffer(GPUDevice& device);

    void SubmitDebugMarker(const char* text);
    GPURenderPass BeginRenderPass(Color_t color, WGPUTextureView);
    // TODO void BeginComputePass();
    // TODO void CopyBufferToBuffer();
    // TODO void CopyBufferToTexture();
    // TODO void CopyTextureToTexture();
    // TODO void ClearBuffer();

    void CreateBuffer();
    void SubmitBuffer();

private:
    WGPUCommandEncoder encoder = nullptr;
    WGPUCommandBuffer command = nullptr;
    WGPUQueue queue = nullptr;
};


#endif //TESTWEBGPU_GPUCOMMANDBUFFER_H
