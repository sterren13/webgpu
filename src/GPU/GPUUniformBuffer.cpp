//
// Created by sterr on 2/08/2023.
//

#include "GPUUniformBuffer.h"

GPUUniformBuffer::GPUUniformBuffer(GPUDevice& device, uint64_t size) : GPUBuffer(device, size, CopyDst | Uniform) {

}
