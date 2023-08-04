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
#include "GPU/GPUVertexBuffer.h"
#include "GPU/GPUIndexBuffer.h"
#include "GPU/GPUUniformBuffer.h"
#include "GPU/GPUBindingGroup.h"
#include "GPU/GPUTexture.h"
#include <iostream>

int main(int, char**){
    GPUInstance g_instance;

    window w("webgpu test", 640, 480, false, true);

    GPUSurface g_surface(g_instance, w);

    GPUAdapter g_adapter(g_instance, g_surface);
    //g_adapter.inspect();

    GPUDevice g_device(g_adapter);
    //g_device.inspect();

    GPUSwapChain g_swapChain(g_surface, g_adapter, g_device);

    WGPUQueue queue = wgpuDeviceGetQueue(g_device.device);

    std::cout << "Create shader \n";
    const char* shaderSource = R"(
    @group(0) @binding(0) var<uniform> uTime: f32;

    struct VertexInput {
        @location(0) position: vec2f,
        @location(1) color: vec3f,
    };
    struct VertexOutput {
        @builtin(position) position: vec4f,
        @location(0) color: vec3f,
    };

    @vertex
    fn vs_main(in: VertexInput) -> VertexOutput {
        var out: VertexOutput;
        let ratio = 640.0 / 480.0;
        // We move the scene depending on the time
        var offset = vec2f(-0.6875, -0.463);
        offset += 0.3 * vec2f(cos(uTime), sin(uTime));
        out.position = vec4f(in.position.x + offset.x, (in.position.y + offset.y) * ratio, 0.0, 1.0);
        out.color = in.color;
        return out;
    }

    @fragment
    fn fs_main(in: VertexOutput) -> @location(0) vec4f {
        return vec4f(in.color, 1.0);
    }
    )";
    GPUShader g_shader(g_device, shaderSource);

    // create vertex buffer
    std::cout << "Create vertex buffer\n";
    std::vector<float> vertexData = {
            // x,   y,     r,   g,   b
            -0.5, -0.5,   1.0, 0.0, 0.0,
            +0.5, -0.5,   0.0, 1.0, 0.0,
            +0.5, +0.5,   0.0, 0.0, 1.0,
            -0.5, +0.5,   1.0, 1.0, 0.0
    };

    int vertexCount = static_cast<int>(vertexData.size() / 5);
    GPUVertexBuffer vertexBuffer1(g_device, BufferLayout({
        BufferElement(DataType::Float32x2, "Pos"),
        BufferElement(DataType::Float32x3, "Color")
    }), vertexCount);

    std::cout << "write to vertex buffer\n";
    vertexBuffer1.Write(0, vertexData.data(), sizeof(float)*5*4);

    std::vector<uint16_t> indexData = {
            0, 1, 2, // Triangle #01
            0, 2, 3  // Triangle #1
    };

    GPUIndexBuffer IndexBuffer(g_device, 6, IndexFormat::Uint16);
    IndexBuffer.Write(0, indexData.data(), sizeof(uint16_t)*6);

    GPUUniformBuffer uniform(g_device, sizeof(float));
    GPUTexture texture(g_device);
    GPUBindingGroup bindingGroup(g_device,
                                 {
                                            {1, ShaderStage::Fragment, texture}
                                          },
                                 {
                                            {0, ShaderStage::Vertex, 0, sizeof(float ), uniform}
                                          }
                                 );

    std::cout << "Create pipeline \n";
    GPURenderPipeline g_Pipeline(g_device, g_shader, g_swapChain.swapChainFormat, vertexBuffer1, bindingGroup);

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

    float currentTime = 1.0f;
    uniform.Write(0, &currentTime, sizeof(float));

    std::cout << std::endl;

    while (!w.Update()){

        // update uniform buffer
        float t = static_cast<float>(glfwGetTime());
        uniform.Write(0, &t, sizeof(float ));

        // Get the texture where to draw the next frame
        WGPUTextureView nextTexture = g_swapChain.CurrentTextureView();
        // Getting the texture may fail, in particular if the window has been resized
        // and thus the target surface changed.
        if (!nextTexture) {
            std::cerr << "Cannot acquire next swap chain texture" << std::endl;
            break;
        }

        GPUCommandBuffer g_Command(g_device);

        GPURenderPass g_RenderPass = g_Command.BeginRenderPass({0.0f, 0.0f, 0.0f, 1.0f}, nextTexture);
        g_RenderPass.SetPipeline(g_Pipeline);
        g_RenderPass.SetVertexBuffer(0, vertexBuffer1, 0);
        g_RenderPass.SetIndexBuffer(IndexBuffer, 0);

        g_RenderPass.SetBindGroup(bindingGroup, 0);
        g_RenderPass.DrawIndexed(6, 1, 0, 0);
        g_RenderPass.EndRenderPass();

        wgpuTextureViewRelease(nextTexture);

        g_Command.CreateBuffer();
        g_Command.SubmitBuffer();

        // We can tell the swap chain to present the next texture.
        g_swapChain.Present();
    }

    return 0;
}