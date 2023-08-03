//
// Created by sterr on 2/08/2023.
//

#ifndef TESTWEBGPU_GPUBINDINGGROUP_H
#define TESTWEBGPU_GPUBINDINGGROUP_H
#include "GPUDevice.h"
#include "GPUUniformBuffer.h"

enum class ShaderStage {
    None,
    Vertex,
    Fragment,
    Compute
};

class GPUBindingGroup {
public:
    GPUBindingGroup(GPUDevice& device, uint32_t slot, ShaderStage stage, GPUUniformBuffer& uniformBuffer);

private:
    friend class GPURenderPipeline;
    friend class GPURenderPass;

private:
    WGPUBindGroupLayoutEntry bindingLayout{};
    WGPUPipelineLayoutDescriptor layoutDesc{};
    WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc{};
    WGPUBindGroupLayout bindGroupLayout = nullptr;
    WGPUBindGroupEntry binding{};
    WGPUBindGroupDescriptor bindGroupDesc{};
    WGPUPipelineLayout layout;
    WGPUBindGroup bindGroup;
};


#endif //TESTWEBGPU_GPUBINDINGGROUP_H
