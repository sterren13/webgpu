//
// Created by sterr on 30/06/2023.
//

#ifndef TESTWEBGPU_WEBGPU_RELEASE_H
#define TESTWEBGPU_WEBGPU_RELEASE_H
#include "webgpu/webgpu.h"

// Dawn and wgpu-native do not agree yet on the lifetime management
// of objects. We align on Dawn convention of calling "release" the
// methods that free memory for objects created with wgpuCreateSomething.
// (The key difference is that Dawn also offers a "reference" function to
// increment a reference counter, and release decreases this counter and
// actually frees memory only when the counter gets to 0)
#include "webgpu/wgpu.h"
#define wgpuInstanceRelease wgpuInstanceDrop
#define wgpuAdapterRelease wgpuAdapterDrop
#define wgpuBindGroupRelease wgpuBindGroupDrop
#define wgpuBindGroupLayoutRelease wgpuBindGroupLayoutDrop
#define wgpuBufferRelease wgpuBufferDrop
#define wgpuCommandBufferRelease wgpuCommandBufferDrop
#define wgpuCommandEncoderRelease wgpuCommandEncoderDrop
#define wgpuRenderPassEncoderRelease wgpuRenderPassEncoderDrop
#define wgpuComputePassEncoderRelease wgpuComputePassEncoderDrop
#define wgpuRenderBundleEncoderRelease wgpuRenderBundleEncoderDrop
#define wgpuComputePipelineRelease wgpuComputePipelineDrop
#define wgpuDeviceRelease wgpuDeviceDrop
#define wgpuPipelineLayoutRelease wgpuPipelineLayoutDrop
#define wgpuQuerySetRelease wgpuQuerySetDrop
#define wgpuRenderBundleRelease wgpuRenderBundleDrop
#define wgpuRenderPipelineRelease wgpuRenderPipelineDrop
#define wgpuSamplerRelease wgpuSamplerDrop
#define wgpuShaderModuleRelease wgpuShaderModuleDrop
#define wgpuSurfaceRelease wgpuSurfaceDrop
#define wgpuSwapChainRelease wgpuSwapChainDrop
#define wgpuTextureRelease wgpuTextureDrop
#define wgpuTextureViewRelease wgpuTextureViewDrop
#endif //TESTWEBGPU_WEBGPU_RELEASE_H
