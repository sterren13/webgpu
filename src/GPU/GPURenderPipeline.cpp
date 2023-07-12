//
// Created by arno on 9/07/23.
//

#include "GPURenderPipeline.h"

GPURenderPipeline::GPURenderPipeline(GPUDevice& device, GPUShader& shader, WGPUTextureFormat swapChainFormat, GPUVertexBuffer& VertexBuffers) {
    pipelineDesc.nextInChain = nullptr;

    // vertex state
    pipelineDesc.vertex.bufferCount = 0;
    pipelineDesc.vertex.buffers = nullptr;
    // shader
    pipelineDesc.vertex.bufferCount = 1;
    pipelineDesc.vertex.buffers = &VertexBuffers.vertexBufferLayout;
    pipelineDesc.vertex.module = shader.shaderModule;
    pipelineDesc.vertex.entryPoint = "vs_main";
    pipelineDesc.vertex.constantCount = 0;
    pipelineDesc.vertex.constants = nullptr;

    // primitive state
    pipelineDesc.primitive.topology = WGPUPrimitiveTopology_TriangleList;
    pipelineDesc.primitive.stripIndexFormat = WGPUIndexFormat_Undefined;
    pipelineDesc.primitive.frontFace = WGPUFrontFace_CCW;
    pipelineDesc.primitive.cullMode = WGPUCullMode_None;

    // fragment state
    fragmentState.module = shader.shaderModule;
    fragmentState.entryPoint = "fs_main";
    fragmentState.constantCount = 0;
    fragmentState.constants = nullptr;
    // blend state
    blendState.color.srcFactor = WGPUBlendFactor_SrcAlpha;
    blendState.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
    blendState.color.operation = WGPUBlendOperation_Add;
    blendState.alpha.srcFactor = WGPUBlendFactor_Zero;
    blendState.alpha.dstFactor = WGPUBlendFactor_One;
    blendState.alpha.operation = WGPUBlendOperation_Add;

    colorTarget.format = swapChainFormat;
    colorTarget.blend = &blendState;
    colorTarget.writeMask = WGPUColorWriteMask_All;

    fragmentState.targetCount = 1;
    fragmentState.targets = &colorTarget;

    pipelineDesc.fragment = &fragmentState;

    // depth state
    pipelineDesc.depthStencil = nullptr;

    // multi-sampling
    pipelineDesc.multisample.count = 1;
    pipelineDesc.multisample.mask = ~0u;
    pipelineDesc.multisample.alphaToCoverageEnabled = false;

    pipelineDesc.layout = nullptr;

    pipeline = wgpuDeviceCreateRenderPipeline(device.device, &pipelineDesc);
}
