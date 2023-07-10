//
// Created by arno on 10/07/23.
//

#include "GPUShader.h"

GPUShader::GPUShader(GPUDevice& device, const char* shader) {
    shaderDesc.hintCount = 0;
    shaderDesc.hints = nullptr;
    shaderCodeDesc.chain.next = nullptr;
    shaderCodeDesc.chain.sType = WGPUSType_ShaderModuleWGSLDescriptor;
    shaderDesc.nextInChain = &shaderCodeDesc.chain;
    shaderCodeDesc.code = shader;
    shaderModule = wgpuDeviceCreateShaderModule(device.device, &shaderDesc);
}
