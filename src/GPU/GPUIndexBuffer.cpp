//
// Created by sterr on 29/07/2023.
//

#include "GPUIndexBuffer.h"
#include <iostream>

GPUIndexBuffer::GPUIndexBuffer(GPUDevice& device, uint64_t Count, IndexFormat Format)
    : GPUBuffer(device, Count * sizeof(uint16_t), CopyDst | Index), Size(Count * sizeof(uint16_t)) {
    switch (Format) {
        case IndexFormat::Uint16:
            format = WGPUIndexFormat::WGPUIndexFormat_Uint16;
            std::cout << "Index format uint16\n";
            break;
        case IndexFormat::Uint32:
            format = WGPUIndexFormat::WGPUIndexFormat_Uint32;
            std::cout << "Index format uint32\n";
            break;
    }
}
