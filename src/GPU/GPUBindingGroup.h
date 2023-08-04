//
// Created by sterr on 2/08/2023.
//

#ifndef TESTWEBGPU_GPUBINDINGGROUP_H
#define TESTWEBGPU_GPUBINDINGGROUP_H
#include "GPUDevice.h"
#include "GPUUniformBuffer.h"
#include "GPUTexture.h"
#include <initializer_list>
#include <vector>

enum class ShaderStage {
    None,
    Vertex,
    Fragment,
    Compute
};

struct UniformBinding {
    uint32_t Slot;
    ShaderStage Stage; // TODO fix | for multiple options
    uint64_t Offset;
    uint64_t Size;
    GPUUniformBuffer& uniformBuffer;
};

struct TextureBinding {
    uint32_t Slot;
    ShaderStage Stage;
    GPUTexture& texture;
};

class GPUBindingGroup {
public:
    GPUBindingGroup(GPUDevice& device, std::initializer_list<TextureBinding> Textures, std::initializer_list<UniformBinding> UniformBuffers);

private:
    friend class GPURenderPipeline;
    friend class GPURenderPass;

private:
    std::vector<WGPUBindGroupLayoutEntry> bindingLayouts;
    WGPUPipelineLayoutDescriptor layoutDesc{};
    WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc{};
    WGPUBindGroupLayout bindGroupLayout = nullptr;
    std::vector<WGPUBindGroupEntry> bindings;
    WGPUBindGroupDescriptor bindGroupDesc{};
    WGPUPipelineLayout layout;
    WGPUBindGroup bindGroup;
};


#endif //TESTWEBGPU_GPUBINDINGGROUP_H
