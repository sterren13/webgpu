//
// Created by arno on 12/07/23.
//

#include "GPUVertexBuffer.h"

BufferElement::BufferElement(DataType type, const std::string &name)
: Name(name), Type(type), Size(Get_DataTypeSize(type)), ComponentCount(Get_ComponentCount(type)) {}

const uint64_t BufferElement::Get_DataTypeSize(DataType type) {
    switch (type) {
        case DataType::Undefined : return 0;
        case DataType::Uint8x2: return 2;
        case DataType::Uint8x4: return 4;
        case DataType::Int8x2: return 2;
        case DataType::Int8x4: return 4;
        case DataType::Unorm8x2: return 2;
        case DataType::Unorm8x4: return 4;
        case DataType::Norm8x2: return 2;
        case DataType::Norm8x4: return 4;
        case DataType::Uint16x2: return 4;
        case DataType::Uint16x4: return 8;
        case DataType::Int16x2: return 4;
        case DataType::Int16x4: return 8;
        case DataType::Unorm16x2: return 4;
        case DataType::Unorm16x4: return 8;
        case DataType::Norm16x2: return 4;
        case DataType::Norm16x4: return 8;
        case DataType::Float16x2: return 4;
        case DataType::Float16x4: return 8;
        case DataType::Float32: return 4;
        case DataType::Float32x2: return 8;
        case DataType::Float32x3: return 12;
        case DataType::Float32x4: return 16;
        case DataType::Uint32: return 4;
        case DataType::Uint32x2: return 8;
        case DataType::Uint32x3: return 12;
        case DataType::Uint32x4: return 16;
        case DataType::Int32: return 4;
        case DataType::Int32x2: return 8;
        case DataType::Int32x3: return 12;
        case DataType::Int32x4: return 16;
        // TODO case DataType::Force32: return
    }
    return 0;
}

const uint64_t BufferElement::Get_ComponentCount(DataType type) {
    switch (type) {
        case DataType::Undefined : return 0;
        case DataType::Uint8x2: return 2;
        case DataType::Uint8x4: return 4;
        case DataType::Int8x2: return 2;
        case DataType::Int8x4: return 4;
        case DataType::Unorm8x2: return 2;
        case DataType::Unorm8x4: return 4;
        case DataType::Norm8x2: return 2;
        case DataType::Norm8x4: return 4;
        case DataType::Uint16x2: return 2;
        case DataType::Uint16x4: return 4;
        case DataType::Int16x2: return 2;
        case DataType::Int16x4: return 4;
        case DataType::Unorm16x2: return 2;
        case DataType::Unorm16x4: return 4;
        case DataType::Norm16x2: return 2;
        case DataType::Norm16x4: return 4;
        case DataType::Float16x2: return 2;
        case DataType::Float16x4: return 4;
        case DataType::Float32: return 1;
        case DataType::Float32x2: return 2;
        case DataType::Float32x3: return 3;
        case DataType::Float32x4: return 4;
        case DataType::Uint32: return 1;
        case DataType::Uint32x2: return 2;
        case DataType::Uint32x3: return 3;
        case DataType::Uint32x4: return 4;
        case DataType::Int32: return 1;
        case DataType::Int32x2: return 2;
        case DataType::Int32x3: return 3;
        case DataType::Int32x4: return 4;
            // TODO case DataType::Force32: return
    }
}

BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements) : BufferElements(elements) {
    Calculate();
}

void BufferLayout::PusheLements(std::initializer_list<BufferElement> elements) {
    for (auto& element : elements)
        BufferElements.push_back(element);
    Calculate();
}

void BufferLayout::Calculate() {
    size_t offset = 0;
    Stride = 0;
    BufferAttributes.clear();
    for (auto& element : BufferElements){
        WGPUVertexAttribute attribute;
        attribute.offset = offset;
        attribute.format = ;

        BufferAttributes.push_back()
    }
}

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
