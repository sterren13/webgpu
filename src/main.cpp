#include "GPU/GPUInstance.h"
#include "window.h"
#include "GPU/GPUSurface.h"
#include "GPU/GPUAdapter.h"
#include "GPU/GPUDevice.h"
#include "GPU/GPUSwapChain.h"
#include "GPU/GPUCommandBuffer.h"

int main(int, char**){
    GPUInstance g_instance;

    window w("webgpu test", 640, 480, false, true);

    GPUSurface g_surface(g_instance, w);

    GPUAdapter g_adapter(g_instance, g_surface);
    //g_adapter.inspect();

    GPUDevice g_device(g_adapter);
    //g_device.inspect();

    GPUSwapChain g_swapChain(g_device, g_adapter, g_surface);

    while (!w.Update()){
        auto view = g_swapChain.GetCurrentView();
        GPUCommandBuffer command(g_device);
        GPURenderPass renderPass = command.BeginRenderPass({1.0f, 0.0f, 0.0f, 1.0f}, view);
        renderPass.EndRenderPass();
        g_swapChain.ReleaseView(view);
        command.SubmitBuffer();
        g_swapChain.Present();
    }

    return 0;
}