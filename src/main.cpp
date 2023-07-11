#include "GPU/GPUInstance.h"
#include "window.h"
#include "GPU/GPUSurface.h"
#include "GPU/GPUAdapter.h"
#include "GPU/GPUDevice.h"
#include "GPU/GPUCommandBuffer.h"
#include "GPU/GPUSwapChain.h"
#include "GPU/GPUShader.h"
#include "GPU/GPURenderPipeline.h"
#include "GPU/GPUBuffer.h"
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

    const char* shaderSource = R"(
    @vertex
    fn vs_main(@builtin(vertex_index) in_vertex_index: u32) -> @builtin(position) vec4<f32> {
        var p = vec2f(0.0, 0.0);
        if (in_vertex_index == 0u) {
            p = vec2f(-0.5, -0.5);
        } else if (in_vertex_index == 1u) {
            p = vec2f(0.5, -0.5);
        } else {
            p = vec2f(0.0, 0.5);
        }
        return vec4f(p, 0.0, 1.0);
    }

    @fragment
    fn fs_main() -> @location(0) vec4f {
        return vec4f(0.0, 0.4, 1.0, 1.0);
    }
    )";
    GPUShader g_shader(g_device, shaderSource);
    GPURenderPipeline g_Pipeline(g_device, g_shader, g_swapChain.swapChainFormat);

    GPUBuffer buffer1(g_device, 16, CopyDst | CopySrc);
    GPUBuffer buffer2(g_device, 16, CopyDst | MapRead);

    std::cout << "Uploading data to the GPU.. \n";
    std::vector<unsigned char> numbers(16);
    for (unsigned char i = 0; i < 16; ++i) numbers[i] = i;

    buffer1.Write(0, numbers.data(), numbers.size());

    std::cout << "Start copy buffer1 to buffer 2 \n";

    GPUCommandBuffer CopyCommand(g_device);
    CopyCommand.CopyBufferToBuffer(buffer1, 0, buffer2, 0, 16);
    CopyCommand.CreateBuffer();
    CopyCommand.SubmitBuffer();

    std::cout << "Start downloading result data from the GPU... \n";

    buffer2.AsyncRead([](unsigned char *bufferdata) {
        std::cout << "bufferData = [";
        for (unsigned char i = 0; i < 16; ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << (int) bufferdata[i];
        }
        std::cout << "]\n";
    }, 0, 16);

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
        g_RenderPass.SetPipeline(g_Pipeline);
        g_RenderPass.Draw( 3, 1, 0, 0);
        g_RenderPass.EndRenderPass();

        wgpuTextureViewRelease(nextTexture);

        g_Command.CreateBuffer();
        g_Command.SubmitBuffer();

        // We can tell the swap chain to present the next texture.
        g_swapChain.Present();
    }

    return 0;
}