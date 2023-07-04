//
// Created by sterr on 2/07/2023.
//

#include "GPUSurface.h"
#include "glfw3webgpu.h"


GPUSurface::GPUSurface(GPUInstance& instance, window& w) {
    surface = glfwGetWGPUSurface(instance.m_instance, w.m_Window);
}

GPUSurface::~GPUSurface() {

}