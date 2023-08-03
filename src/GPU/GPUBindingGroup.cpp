//
// Created by sterr on 2/08/2023.
//

#include "GPUBindingGroup.h"

void setDefault(WGPUBindGroupLayoutEntry &bindingLayout) {
    bindingLayout.buffer.nextInChain = nullptr;
    bindingLayout.buffer.type = WGPUBufferBindingType_Undefined;
    bindingLayout.buffer.hasDynamicOffset = false;

    bindingLayout.sampler.nextInChain = nullptr;
    bindingLayout.sampler.type = WGPUSamplerBindingType_Undefined;

    bindingLayout.storageTexture.nextInChain = nullptr;
    bindingLayout.storageTexture.access = WGPUStorageTextureAccess_Undefined;
    bindingLayout.storageTexture.format = WGPUTextureFormat_Undefined;
    bindingLayout.storageTexture.viewDimension = WGPUTextureViewDimension_Undefined;

    bindingLayout.texture.nextInChain = nullptr;
    bindingLayout.texture.multisampled = false;
    bindingLayout.texture.sampleType = WGPUTextureSampleType_Undefined;
    bindingLayout.texture.viewDimension = WGPUTextureViewDimension_Undefined;
}

GPUBindingGroup::GPUBindingGroup(GPUDevice &device, uint32_t slot, ShaderStage stage, GPUUniformBuffer& uniformBuffer) {
    // bindingLayout TODO list of bindinglayouts and texturers
    setDefault(bindingLayout);
    bindingLayout.binding = slot;
    switch (stage) {
        case ShaderStage::Vertex:
            bindingLayout.visibility = WGPUShaderStage_Vertex;
            break;
        case ShaderStage::Fragment:
            bindingLayout.visibility = WGPUShaderStage_Fragment;
            break;
        case ShaderStage::Compute:
            bindingLayout.visibility = WGPUShaderStage_Compute;
            break;
        default:
            bindingLayout.visibility = WGPUShaderStage_None;
            break;
    }
    bindingLayout.buffer.type = WGPUBufferBindingType_Uniform;
    bindingLayout.buffer.minBindingSize = uniformBuffer.Size(); // TODO set to input in list of uniform buffers

    // Crate binding group layout
    bindGroupLayoutDesc.nextInChain = nullptr;
    bindGroupLayoutDesc.entryCount = 1; // TODO change to layout count
    bindGroupLayoutDesc.entries = &bindingLayout; // TODO change to list of binding layouts
    bindGroupLayout = wgpuDeviceCreateBindGroupLayout(device.device, &bindGroupLayoutDesc);

    // create pipeline layout
    layoutDesc.nextInChain = nullptr;
    layoutDesc.bindGroupLayoutCount = 1;
    layoutDesc.bindGroupLayouts = &bindGroupLayout;
    layout = wgpuDeviceCreatePipelineLayout(device.device, &layoutDesc);

    // crate entries
    // TODO list of bindings
    binding.nextInChain = nullptr;
    binding.binding = slot; // TODO set to uniform buffer inputs
    binding.buffer = uniformBuffer.buffer; // TODO set input uniform buffer
    binding.offset = 0; // TODO input in list of uniform buffers
    binding.size = uniformBuffer.Size(); // TODO set to input in list of uniform buffers

    // create binding group
    bindGroupDesc.nextInChain = nullptr;
    bindGroupDesc.layout = bindGroupLayout;
    bindGroupDesc.entryCount = bindGroupLayoutDesc.entryCount;
    bindGroupDesc.entries = &binding; // TODO list of entries
    bindGroup = wgpuDeviceCreateBindGroup(device.device, &bindGroupDesc);
}
