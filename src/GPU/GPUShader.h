//
// Created by arno on 10/07/23.
//

#ifndef TESTWEBGPU_GPUSHADER_H
#define TESTWEBGPU_GPUSHADER_H
#include "webgpu/webgpu.h"
#include "GPUDevice.h"

class GPUShader {
public:
    GPUShader(GPUDevice& device, const char* shader);
private:
    friend class GPURenderPipeline;

    WGPUShaderModuleWGSLDescriptor shaderCodeDesc{};
    WGPUShaderModuleDescriptor shaderDesc{};
    WGPUShaderModule shaderModule;
};


#endif //TESTWEBGPU_GPUSHADER_H
