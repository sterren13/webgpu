//
// Created by sterr on 4/08/2023.
//

#ifndef TESTWEBGPU_GPUTEXTURE_H
#define TESTWEBGPU_GPUTEXTURE_H
#include "GPUDevice.h"
#include <webgpu/webgpu.h>
#include <webgpu/wgpu.h>

class GPUTexture {
public:
    GPUTexture(GPUDevice& device);

    ~GPUTexture();

private:
    friend class GPUBindingGroup;
private:
    WGPUTextureDescriptor textureDesc;
    WGPUTextureViewDescriptor textureViewDesc;
    WGPUTexture texture = nullptr;
    WGPUTextureView textureView = nullptr;
    WGPUQueue queue = nullptr;
};


#endif //TESTWEBGPU_GPUTEXTURE_H
