//
// Created by arno on 11/07/23.
//

#ifndef TESTWEBGPU_GPUBUFFER_H
#define TESTWEBGPU_GPUBUFFER_H
#include "webgpu/webgpu.h"
#include "GPUDevice.h"
#include <functional>

const WGPUBufferUsageFlags MapRead = WGPUBufferUsage_MapRead;
const WGPUBufferUsageFlags MapWrite = WGPUBufferUsage_MapWrite;
const WGPUBufferUsageFlags CopySrc = WGPUBufferUsage_CopySrc;
const WGPUBufferUsageFlags CopyDst = WGPUBufferUsage_CopyDst;
const WGPUBufferUsageFlags Index = WGPUBufferUsage_Index;
const WGPUBufferUsageFlags Vertex = WGPUBufferUsage_Vertex;
const WGPUBufferUsageFlags Uniform = WGPUBufferUsage_Uniform;
const WGPUBufferUsageFlags Storage = WGPUBufferUsage_Storage;
const WGPUBufferUsageFlags Indirect = WGPUBufferUsage_Indirect;
const WGPUBufferUsageFlags QueryResolve = WGPUBufferUsage_QueryResolve;
const WGPUBufferUsageFlags Force32 = WGPUBufferUsage_Force32;

class GPUBuffer {
public:
    GPUBuffer(GPUDevice& device, uint64_t size, WGPUBufferUsageFlags usage);
    ~GPUBuffer();
    void Write(uint64_t Offset, const void* data, size_t size);
    void AsyncRead(std::function<void(unsigned char* bufferData)> CallBack, size_t offset, size_t size);

private:
    friend class GPUCommandBuffer;
    friend class GPURenderPass;

    static void ReadCallBack(WGPUBufferMapAsyncStatus status, void* pUserData);

    struct ContextRead {
        WGPUBuffer buffer;
        size_t offset;
        size_t size;
        std::function<void(unsigned char *)> CallBack;
    }contextRead;

    WGPUBufferDescriptor bufferDesc = {};
    WGPUBuffer buffer;
    WGPUQueue queue = nullptr;
};


#endif //TESTWEBGPU_GPUBUFFER_H
