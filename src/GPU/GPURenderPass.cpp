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
