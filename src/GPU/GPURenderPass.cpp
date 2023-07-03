//
// Created by sterr on 3/07/2023.
//

#include "GPURenderPass.h"

GPURenderPass::GPURenderPass(WGPURenderPassEncoder e) : encoder(e) {

}

void GPURenderPass::EndRenderPass() {
    wgpuRenderPassEncoderEnd(encoder);
}
