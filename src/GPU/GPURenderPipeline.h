//
// Created by arno on 9/07/23.
//

#ifndef TESTWEBGPU_GPURENDERPIPELINE_H
#define TESTWEBGPU_GPURENDERPIPELINE_H
#include <webgpu/webgpu.h>
#include "GPUShader.h"
#include "GPUDevice.h"

class GPURenderPipeline {
public:
    GPURenderPipeline(GPUDevice& device, GPUShader& shader, WGPUTextureFormat swapChainFormat);
private:
    friend class GPURenderPass;

    WGPUColorTargetState colorTarget{};
    WGPUBlendState blendState{};
    WGPUFragmentState fragmentState{};
    WGPURenderPipelineDescriptor pipelineDesc {};
    WGPURenderPipeline pipeline;
};


#endif //TESTWEBGPU_GPURENDERPIPELINE_H
