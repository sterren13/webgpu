//
// Created by sterr on 2/08/2023.
//

#ifndef TESTWEBGPU_GPUUNIFORMBUFFER_H
#define TESTWEBGPU_GPUUNIFORMBUFFER_H
#include "GPUBuffer.h"

class GPUUniformBuffer : public GPUBuffer {
public:
    GPUUniformBuffer(GPUDevice& device, uint64_t size);

private:

};


#endif //TESTWEBGPU_GPUUNIFORMBUFFER_H
