//
// Created by arno on 9/07/23.
//

#ifndef TESTWEBGPU_GPURENDERPIPELINE_H
#define TESTWEBGPU_GPURENDERPIPELINE_H
#include <webgpu/webgpu.h>
#include "GPUShader.h"
#include "GPUDevice.h"
#include "GPUVertexBuffer.h"
#include "GPUBindingGroup.h"

class GPURenderPipeline {
public:
    GPURenderPipeline(GPUDevice& device, GPUShader& shader, WGPUTextureFormat swapChainFormat, GPUVertexBuffer& VertexBuffers, GPUBindingGroup& bindingGroup);
private:
    friend class GPURenderPass;

    WGPUPipelineLayoutDescriptor layoutDesc{};
    WGPUColorTargetState colorTarget{};
    WGPUBlendState blendState{};
    WGPUFragmentState fragmentState{};
    WGPURenderPipelineDescriptor pipelineDesc {};
    WGPURenderPipeline pipeline;
    WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc{};
};


#endif //TESTWEBGPU_GPURENDERPIPELINE_H
