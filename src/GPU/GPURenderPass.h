//
// Created by sterr on 3/07/2023.
//

#ifndef TESTWEBGPU_GPURENDERPASS_H
#define TESTWEBGPU_GPURENDERPASS_H
#include <webgpu/webgpu.h>
#include "GPURenderPipeline.h"
#include "GPUVertexBuffer.h"
#include "GPUIndexBuffer.h"

class GPURenderPass {
public:
    GPURenderPass(WGPURenderPassEncoder e);

    void SetPipeline(GPURenderPipeline& pipeline);
    void SetVertexBuffer(uint32_t slot, GPUVertexBuffer &buffer, uint64_t offset);
    void SetIndexBuffer(GPUIndexBuffer& indexBuffer, uint64_t offset);
    void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
    void DrawIndexed(uint64_t IndexCount, uint64_t InstanceCount, uint64_t FirstIndex, uint64_t FirstInstance);
    //TODO void DrawIndirect();
    //TODO void DrawIndexedIndirect();
    //TODO void SetBindGroup();
    //TODO void PushDebugGroup();
    //TODO void PopDebugGroup();
    //TODO void InsertDebugMarker();
    //TODO void SetViewport();
    //TODO void SetScissorRect();
    //TODO void SetBlendConstant();
    //TODO void SetStencilReference();
    //TODO void BeginOcclusionQuery();

    void EndRenderPass();
private:
    WGPURenderPassEncoder encoder;
};

#endif //TESTWEBGPU_GPURENDERPASS_H
