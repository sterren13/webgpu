//
// Created by sterr on 3/07/2023.
//

#ifndef TESTWEBGPU_GPURENDERPASS_H
#define TESTWEBGPU_GPURENDERPASS_H
#include <webgpu/webgpu.h>

class GPURenderPass {
public:
    GPURenderPass(WGPURenderPassEncoder e);

    //TODO void SetPipeline();
    //TODO void SetIndexBuffer();
    //TODO void SetVertexBuffer();
    //TODO void Draw();
    //TODO void DrawIndexed();
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
