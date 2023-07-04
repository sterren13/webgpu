//
// Created by sterr on 2/07/2023.
//

#include "GPUInstance.h"
#include "webgpu/wgpu.h"
#include <iostream>

GPUInstance::GPUInstance() {
    // create a descriptor
    WGPUInstanceDescriptor desc = {};
    desc.nextInChain = nullptr;

    // create instance using descriptor
    m_instance = wgpuCreateInstance(&desc);
    if (!m_instance) {
        std::cerr << "[Error] Could not initialize WebGPU! \n";
        return;
    }
    std::cout << "[info] wgpu instance: " << m_instance << "\n";
}

GPUInstance::~GPUInstance() {
    if (m_instance)
        wgpuInstanceRelease(m_instance);
}
