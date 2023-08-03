//
// Created by sterr on 2/08/2023.
//

#ifndef TESTWEBGPU_GPUUNIFORMBUFFER_H
#define TESTWEBGPU_GPUUNIFORMBUFFER_H
#include "GPUBuffer.h"

class GPUUniformBuffer : public GPUBuffer {
public:
    GPUUniformBuffer(GPUDevice& device, uint64_t size);
    inline uint64_t Size() const {return m_size;}

private:
    uint64_t m_size;
};


#endif //TESTWEBGPU_GPUUNIFORMBUFFER_H
