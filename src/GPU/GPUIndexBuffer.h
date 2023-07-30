//
// Created by sterr on 29/07/2023.
//

#ifndef TESTWEBGPU_GPUINDEXBUFFER_H
#define TESTWEBGPU_GPUINDEXBUFFER_H
#include "GPUBuffer.h"

enum class IndexFormat {
    Uint16,
    Uint32
};

class GPUIndexBuffer : public GPUBuffer {
public:
    GPUIndexBuffer(GPUDevice& device, uint64_t Count, IndexFormat Format);
private:
    friend class GPURenderPass;
private:
    uint64_t Size;
    WGPUIndexFormat format = WGPUIndexFormat::WGPUIndexFormat_Undefined;
};


#endif //TESTWEBGPU_GPUINDEXBUFFER_H