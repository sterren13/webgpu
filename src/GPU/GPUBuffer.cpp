//
// Created by arno on 11/07/23.
//

#include "GPUBuffer.h"
#include <iostream>

GPUBuffer::GPUBuffer(GPUDevice& device, uint64_t size, WGPUBufferUsageFlags usage) {
    bufferDesc.nextInChain = nullptr;
    bufferDesc.label = "Buffer data";
    bufferDesc.usage = usage;
    bufferDesc.size = size;
    bufferDesc.mappedAtCreation = false;
    buffer = wgpuDeviceCreateBuffer(device.device, &bufferDesc);
    queue = wgpuDeviceGetQueue(device.device);
}

GPUBuffer::~GPUBuffer() {
    wgpuBufferDestroy(buffer); // free GPU memory
    wgpuBufferReference(buffer); // free in driver side object
}

void GPUBuffer::Write(uint64_t Offset, const void* data, size_t size) {
    wgpuQueueWriteBuffer(queue, buffer, Offset, data, size);
}

void GPUBuffer::AsyncRead(std::function<void(unsigned char *)> CallBack, size_t offset, size_t size) {
    contextRead.buffer = buffer;
    contextRead.size = size;
    contextRead.offset = offset;
    contextRead.CallBack = CallBack;
    wgpuBufferMapAsync(buffer, WGPUMapMode_Read, offset, size, ReadCallBack, (void*)&contextRead);
}

void GPUBuffer::ReadCallBack(WGPUBufferMapAsyncStatus status, void *pUserData) {
    ContextRead* con = reinterpret_cast<ContextRead*>(pUserData);
    if (status != WGPUBufferMapAsyncStatus_Success) return; // TODO add error message
    unsigned char* bufferData = (unsigned char*) wgpuBufferGetConstMappedRange(con->buffer, con->offset, con->size);
    con->CallBack(bufferData);
    wgpuBufferUnmap(con->buffer);
}
