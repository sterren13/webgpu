//
// Created by sterr on 3/07/2023.
//

#include "GPURenderPass.h"


GPURenderPass::GPURenderPass(WGPURenderPassEncoder e) : encoder(e) {

}

void GPURenderPass::EndRenderPass() {
    wgpuRenderPassEncoderEnd(encoder);
}

void GPURenderPass::SetPipeline(GPURenderPipeline &pipeline) {
    wgpuRenderPassEncoderSetPipeline(encoder, pipeline.pipeline);
}

void GPURenderPass::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    wgpuRenderPassEncoderDraw(encoder, vertexCount, instanceCount, firstVertex, firstInstance);
}

void GPURenderPass::SetVertexBuffer(uint32_t slot, GPUVertexBuffer &buffer, uint64_t offset) {
    wgpuRenderPassEncoderSetVertexBuffer(encoder,slot, buffer.buffer, offset, buffer.Size);
}

void GPURenderPass::SetIndexBuffer(GPUIndexBuffer& indexBuffer, uint64_t offset) {
    wgpuRenderPassEncoderSetIndexBuffer(encoder, indexBuffer.buffer, indexBuffer.format, offset, indexBuffer.Size);
}

void GPURenderPass::DrawIndexed(uint64_t IndexCount, uint64_t InstanceCount, uint64_t FirstIndex, uint64_t FirstInstance) {
    wgpuRenderPassEncoderDrawIndexed(encoder, IndexCount, InstanceCount, FirstIndex, 0, 0);
}

void GPURenderPass::SetBindGroup(GPUBindingGroup &bindingGroup, uint32_t slot) {
    wgpuRenderPassEncoderSetBindGroup(encoder, slot, bindingGroup.bindGroup, 0, nullptr);
}
