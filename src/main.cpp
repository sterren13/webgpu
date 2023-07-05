#include "GPU/GPUInstance.h"
#include "window.h"
#include "GPU/GPUSurface.h"
#include "GPU/GPUAdapter.h"
#include "GPU/GPUDevice.h"
#include "GPU/GPUCommandBuffer.h"
#include "GPU/GPUSwapChain.h"
#include <iostream>

int main(int, char**){
    GPUInstance g_instance;

    window w("webgpu test", 640, 480, false, true);

    GPUSurface g_surface(g_instance, w);

    GPUAdapter g_adapter(g_instance, g_surface);
    //g_adapter.inspect();

    GPUDevice g_device(g_adapter);
    //g_device.inspect()

    GPUSwapChain g_swapChain(g_surface, g_adapter, g_device);

    WGPUQueue queue = wgpuDeviceGetQueue(g_device.device);

    while (!w.Update()){
        // Get the texture where to draw the next frame
        WGPUTextureView nextTexture = g_swapChain.CurrentTextureView();
        // Getting the texture may fail, in particular if the window has been resized
        // and thus the target surface changed.
        if (!nextTexture) {
            std::cerr << "Cannot acquire next swap chain texture" << std::endl;
            break;
        }

        GPUCommandBuffer g_Command(g_device);

        GPURenderPass g_RenderPass = g_Command.BeginRenderPass({0.0f, 1.0f, 0.0f, 1.0f}, nextTexture);
        g_RenderPass.EndRenderPass();

        wgpuTextureViewRelease(nextTexture);

        g_Command.CreateBuffer();
        g_Command.SubmitBuffer();

        // We can tell the swap chain to present the next texture.
        g_swapChain.Present();
    }

    return 0;
}