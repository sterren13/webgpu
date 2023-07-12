//
// Created by arno on 12/07/23.
//

#include "GPUVertexBuffer.h"

GPUVertexBuffer::GPUVertexBuffer(GPUDevice& device, uint64_t VertexCount) : GPUBuffer(device, VertexCount*2*sizeof(float), CopyDst | Vertex) {
    // TODO auto gen
    vertexAttrib.shaderLocation = 0;
    vertexAttrib.format = WGPUVertexFormat_Float32x2;
    vertexAttrib.offset = 0;
    vertexBufferLayout.arrayStride = 2 * sizeof(float);
    vertexBufferLayout.stepMode = WGPUVertexStepMode_Vertex;
    vertexBufferLayout.attributeCount = 1;
    vertexBufferLayout.attributes = &vertexAttrib;
}
