//
// Created by arno on 12/07/23.
//

#ifndef TESTWEBGPU_GPUVERTEXBUFFER_H
#define TESTWEBGPU_GPUVERTEXBUFFER_H
#include "GPUBuffer.h"
#include "GPUDevice.h"

class GPUVertexBuffer : public GPUBuffer {
public:
    GPUVertexBuffer(GPUDevice& device, uint64_t VertexCount);

private:
    friend class GPURenderPass;
    friend class GPURenderPipeline;

    WGPUVertexAttribute vertexAttrib;
    WGPUVertexBufferLayout vertexBufferLayout{};
};


#endif //TESTWEBGPU_GPUVERTEXBUFFER_H
