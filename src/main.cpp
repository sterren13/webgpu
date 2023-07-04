#include "GPU/GPUInstance.h"
#include "window.h"
#include "GPU/GPUSurface.h"
#include "GPU/GPUAdapter.h"
#include "GPU/GPUDevice.h"
#include "GPU/GPUSwapChain.h"
#include "GPU/GPUCommandBuffer.h"
#include <iostream>

int main(int, char**){
    GPUInstance g_instance;

    window w("webgpu test", 640, 480, false, true);

    GPUSurface g_surface(g_instance, w);

    GPUAdapter g_adapter(g_instance, g_surface);
    //g_adapter.inspect();

    GPUDevice g_device(g_adapter);
    //g_device.inspect()

    WGPUSwapChainDescriptor swapChainDesc = {};
    swapChainDesc.width = 640;
    swapChainDesc.height = 480;
    swapChainDesc.usage = WGPUTextureUsage_RenderAttachment;
    WGPUTextureFormat swapChainFormat = wgpuSurfaceGetPreferredFormat(g_surface.surface, g_adapter.adapter);
    swapChainDesc.format = swapChainFormat;
    swapChainDesc.presentMode = WGPUPresentMode_Fifo;
    WGPUSwapChain swapChain = wgpuDeviceCreateSwapChain(g_device.device, g_surface.surface, &swapChainDesc);

    WGPUQueue queue = wgpuDeviceGetQueue(g_device.device);

    while (!w.Update()){
        // Get the texture where to draw the next frame
        WGPUTextureView nextTexture = wgpuSwapChainGetCurrentTextureView(swapChain);
        // Getting the texture may fail, in particular if the window has been resized
        // and thus the target surface changed.
        if (!nextTexture) {
            std::cerr << "Cannot acquire next swap chain texture" << std::endl;
            break;
        }
        std::cout << "nextTexture: " << nextTexture << std::endl;

        WGPUCommandEncoderDescriptor commandEncoderDesc = {};
        commandEncoderDesc.nextInChain = nullptr;
        commandEncoderDesc.label = "Command Encoder";
        WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(g_device.device, &commandEncoderDesc);

        // Describe a render pass, which targets the texture view
        WGPURenderPassDescriptor renderPassDesc = {};

        WGPURenderPassColorAttachment renderPassColorAttachment = {};
        // The attachment is tighed to the view returned by the swap chain, so that
        // the render pass draws directly on screen.
        renderPassColorAttachment.view = nextTexture;
        // Not relevant here because we do not use multi-sampling
        renderPassColorAttachment.resolveTarget = nullptr;
        renderPassColorAttachment.loadOp = WGPULoadOp_Clear;
        renderPassColorAttachment.storeOp = WGPUStoreOp_Store;
        renderPassColorAttachment.clearValue = WGPUColor{ 0.9, 0.1, 0.2, 1.0 };
        renderPassDesc.colorAttachmentCount = 1;
        renderPassDesc.colorAttachments = &renderPassColorAttachment;

        // No depth buffer for now
        renderPassDesc.depthStencilAttachment = nullptr;

        // We do not use timers for now neither
        renderPassDesc.timestampWriteCount = 0;
        renderPassDesc.timestampWrites = nullptr;

        renderPassDesc.nextInChain = nullptr;

        // Create a render pass. We end it immediately because we use its built-in
        // mechanism for clearing the screen when it begins (see descriptor).
        WGPURenderPassEncoder renderPass = wgpuCommandEncoderBeginRenderPass(encoder, &renderPassDesc);
        wgpuRenderPassEncoderEnd(renderPass);

        wgpuTextureViewRelease(nextTexture);

        WGPUCommandBufferDescriptor cmdBufferDescriptor = {};
        cmdBufferDescriptor.nextInChain = nullptr;
        cmdBufferDescriptor.label = "Command buffer";
        WGPUCommandBuffer command = wgpuCommandEncoderFinish(encoder, &cmdBufferDescriptor);
        wgpuQueueSubmit(queue, 1, &command);

        // We can tell the swap chain to present the next texture.
        wgpuSwapChainPresent(swapChain);
    }

    return 0;
}