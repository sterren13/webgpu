//
// Created by sterr on 3/07/2023.
//

#include "GPUCommandBuffer.h"
#include <webgpu/wgpu.h>
#include <iostream>

GPUCommandBuffer::GPUCommandBuffer(GPUDevice& device) {
    WGPUCommandEncoderDescriptor encoderDescriptor = {};
    encoderDescriptor.nextInChain = nullptr;
    encoderDescriptor.label = "My command encoder";
    encoder = wgpuDeviceCreateCommandEncoder(device.device, &encoderDescriptor);
    queue = wgpuDeviceGetQueue(device.device);
}

void GPUCommandBuffer::SubmitDebugMarker(const char *text) {
    wgpuCommandEncoderInsertDebugMarker(encoder, text);
}

GPURenderPass GPUCommandBuffer::BeginRenderPass(Color_t color, WGPUTextureView Texture) {
    WGPURenderPassDescriptor renderPassDescriptor = {};

    // add attachments
    // color
    WGPURenderPassColorAttachment renderPassColorAttachment = {};
    renderPassColorAttachment.view = Texture;
    renderPassColorAttachment.resolveTarget = nullptr;
    renderPassColorAttachment.loadOp = WGPULoadOp_Clear;
    renderPassColorAttachment.storeOp = WGPUStoreOp_Store;
    renderPassColorAttachment.clearValue = WGPUColor{color.R, color.G, color.B, color.A};
    renderPassDescriptor.colorAttachmentCount = 1;
    renderPassDescriptor.colorAttachments = &renderPassColorAttachment;
    // depth
    renderPassDescriptor.depthStencilAttachment = nullptr;

    // time
    renderPassDescriptor.timestampWriteCount = 0;
    renderPassDescriptor.timestampWrites = nullptr;

    renderPassDescriptor.nextInChain = nullptr;

    return GPURenderPass(wgpuCommandEncoderBeginRenderPass(encoder, &renderPassDescriptor));
}

void GPUCommandBuffer::CreateBuffer() {
    WGPUCommandBufferDescriptor CommandBufferDescriptor ={};
    CommandBufferDescriptor.nextInChain = nullptr;
    CommandBufferDescriptor.label = "Command buffer";
    command = wgpuCommandEncoderFinish(encoder, &CommandBufferDescriptor);
}

void GPUCommandBuffer::SubmitBuffer() {
    wgpuQueueSubmit(queue, 1, &command);
}

void GPUCommandBuffer::CopyBufferToBuffer(GPUBuffer &Source, uint64_t SourceOffset, GPUBuffer &Destination,
                                          uint64_t DestinationOffset, uint64_t size) {
    wgpuCommandEncoderCopyBufferToBuffer(encoder, Source.buffer, SourceOffset, Destination.buffer, DestinationOffset, size);
}

void GPUCommandBuffer::ClearBuffer(GPUBuffer &Source, uint64_t Offset, uint64_t Size) {
    wgpuCommandEncoderClearBuffer(encoder, Source.buffer, Offset, Size);
}
