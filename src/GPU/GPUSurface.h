//
// Created by sterr on 2/07/2023.
//

#ifndef TESTWEBGPU_GPUSURFACE_H
#define TESTWEBGPU_GPUSURFACE_H
#include "webgpu/webgpu.h"
#include "window.h"
#include "GPUInstance.h"

class GPUSurface {
public:
    GPUSurface(GPUInstance& instance, window& w);
    ~GPUSurface();
private:
    friend class GPUAdapter;
    friend class GPUSwapChain;
    WGPUSurface surface;
};


#endif //TESTWEBGPU_GPUSURFACE_H
