//
// Created by sterr on 3/07/2023.
//

#ifndef TESTWEBGPU_GPUCOMMANDBUFFER_H
#define TESTWEBGPU_GPUCOMMANDBUFFER_H
#include <webgpu/webgpu.h>
#include "GPUDevice.h"
#include "GPURenderPass.h"
#include "GPUTypse.h"
#include "GPUBuffer.h"

class GPUCommandBuffer {
public:
    GPUCommandBuffer(GPUDevice& device);

    void SubmitDebugMarker(const char* text);
    GPURenderPass BeginRenderPass(Color_t color, WGPUTextureView);
    // TODO void BeginComputePass();
    void CopyBufferToBuffer(GPUBuffer& Source, uint64_t SourceOffset, GPUBuffer& Destination,
                            uint64_t DestinationOffset, uint64_t size);
    // TODO void CopyBufferToTexture();
    // TODO void CopyTextureToTexture();
    void ClearBuffer(GPUBuffer& Source, uint64_t Offset = 0, uint64_t Size = 0);

    void CreateBuffer();
    void SubmitBuffer();

private:
    WGPUCommandEncoder encoder = nullptr;
    WGPUCommandBuffer command = nullptr;
    WGPUQueue queue = nullptr;
};


#endif //TESTWEBGPU_GPUCOMMANDBUFFER_H
