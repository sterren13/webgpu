//
// Created by sterr on 4/08/2023.
//

#include "GPUTexture.h"
#include <vector>
#include <assert.h>

GPUTexture::GPUTexture(GPUDevice& device) {
    textureDesc.nextInChain = nullptr;
    textureDesc.label = "Test texture";
    textureDesc.dimension = WGPUTextureDimension_2D;
    textureDesc.size = { 256, 256, 1 };
    textureDesc.mipLevelCount = 1;
    textureDesc.sampleCount = 1;
    textureDesc.format = WGPUTextureFormat_RGBA8Unorm;
    textureDesc.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
    textureDesc.viewFormatCount = 0;
    textureDesc.viewFormats = nullptr;

    texture = wgpuDeviceCreateTexture(device.device, &textureDesc);
    assert(texture != nullptr);

    // create texture view
    textureViewDesc.aspect = WGPUTextureAspect_All;
    textureViewDesc.label = "Test view";
    textureViewDesc.baseArrayLayer = 0;
    textureViewDesc.arrayLayerCount = 1;
    textureViewDesc.baseMipLevel = 0;
    textureViewDesc.mipLevelCount = 1;
    textureViewDesc.dimension = WGPUTextureViewDimension_2D;
    textureViewDesc.format = textureDesc.format;
    textureView = wgpuTextureCreateView(texture, &textureViewDesc);
    assert(textureView != nullptr);

    // TODO change to file
    std::vector<uint8_t> pixels(4 * textureDesc.size.width * textureDesc.size.height);
    for (uint32_t i = 0; i < textureDesc.size.width; ++i) {
        for (uint32_t j = 0; j < textureDesc.size.height; ++j) {
            uint8_t *p = &pixels[4 * (j * textureDesc.size.width + i)];
            p[0] = (i / 16) % 2 == (j / 16) % 2 ? 255 : 0; // r
            p[1] = ((i - j) / 16) % 2 == 0 ? 255 : 0; // g
            p[2] = ((i + j) / 16) % 2 == 0 ? 255 : 0; // b
            p[3] = 255; // a
        }
    }

    WGPUImageCopyTexture destination;
    destination.texture = texture;
    destination.mipLevel = 0;
    destination.origin = {0,0,0};
    destination.aspect = WGPUTextureAspect_All;

    WGPUTextureDataLayout source;
    source.offset = 0;
    source.bytesPerRow = 4 * textureDesc.size.width;
    source.rowsPerImage = textureDesc.size.height;

    queue = wgpuDeviceGetQueue(device.device);
    wgpuQueueWriteTexture(queue, &destination, pixels.data(), pixels.size(), &source, &textureDesc.size);
}

GPUTexture::~GPUTexture() {
    wgpuTextureDestroy(texture);
    wgpuTextureReference(texture);
}
