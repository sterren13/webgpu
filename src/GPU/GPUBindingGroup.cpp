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

GPUBindingGroup::GPUBindingGroup(GPUDevice &device, std::initializer_list<TextureBinding> Textures, std::initializer_list<UniformBinding> UniformBuffers) {
    // binding layouts Uniforms and bindings
    for (auto uniform : UniformBuffers){
        // create layout
        WGPUBindGroupLayoutEntry LayoutEntry;
        setDefault(LayoutEntry);
        LayoutEntry.binding = uniform.Slot;
        switch (uniform.Stage) {
            case ShaderStage::Vertex:
                LayoutEntry.visibility = WGPUShaderStage_Vertex;
                break;
            case ShaderStage::Fragment:
                LayoutEntry.visibility = WGPUShaderStage_Fragment;
                break;
            case ShaderStage::Compute:
                LayoutEntry.visibility = WGPUShaderStage_Compute;
                break;
            default:
                LayoutEntry.visibility = WGPUShaderStage_None;
                break;
        }
        LayoutEntry.buffer.type = WGPUBufferBindingType_Uniform;
        LayoutEntry.buffer.minBindingSize = uniform.uniformBuffer.Size();
        bindingLayouts.push_back(LayoutEntry);

        // crate entries
        WGPUBindGroupEntry binding{};
        binding.nextInChain = nullptr;
        binding.binding = uniform.Slot;
        binding.buffer = uniform.uniformBuffer.buffer;
        binding.offset = uniform.Offset;
        binding.size = uniform.Size;
        bindings.push_back(binding);
    }

    // binding Layouts textures and bindings
    for (auto Texture : Textures){
        // create layout
        WGPUBindGroupLayoutEntry LayoutEntry;
        setDefault(LayoutEntry);

        LayoutEntry.binding = Texture.Slot;
        switch (Texture.Stage) {
            case ShaderStage::Vertex:
                LayoutEntry.visibility = WGPUShaderStage_Vertex;
                break;
            case ShaderStage::Fragment:
                LayoutEntry.visibility = WGPUShaderStage_Fragment;
                break;
            case ShaderStage::Compute:
                LayoutEntry.visibility = WGPUShaderStage_Compute;
                break;
            default:
                LayoutEntry.visibility = WGPUShaderStage_None;
                break;
        }
        LayoutEntry.texture.sampleType = WGPUTextureSampleType_Float; // TODO change to texture property's
        LayoutEntry.texture.viewDimension = WGPUTextureViewDimension_2D; // TODO change to texture property's
        bindingLayouts.push_back(LayoutEntry);

        // crate entries
        WGPUBindGroupEntry binding{};
        binding.binding = Texture.Slot;
        binding.textureView= Texture.texture.textureView;
        bindings.push_back(binding);
    }

    // Crate binding group layout
    bindGroupLayoutDesc.nextInChain = nullptr;
    bindGroupLayoutDesc.entryCount = bindingLayouts.size();
    bindGroupLayoutDesc.entries = bindingLayouts.data();
    bindGroupLayout = wgpuDeviceCreateBindGroupLayout(device.device, &bindGroupLayoutDesc);

    // create pipeline layout
    layoutDesc.nextInChain = nullptr;
    layoutDesc.bindGroupLayoutCount = 1;
    layoutDesc.bindGroupLayouts = &bindGroupLayout;
    layout = wgpuDeviceCreatePipelineLayout(device.device, &layoutDesc);

    // create binding group
    bindGroupDesc.nextInChain = nullptr;
    bindGroupDesc.layout = bindGroupLayout;
    bindGroupDesc.entryCount = bindGroupLayoutDesc.entryCount;
    bindGroupDesc.entries = bindings.data();
    bindGroup = wgpuDeviceCreateBindGroup(device.device, &bindGroupDesc);
}
