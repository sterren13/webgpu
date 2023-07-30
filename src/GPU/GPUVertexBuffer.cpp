//
// Created by arno on 12/07/23.
//

#include "GPUVertexBuffer.h"

BufferElement::BufferElement(DataType type, const std::string &name)
: Name(name), Type(type), size(Get_DataTypeSize(type)), ComponentCount(Get_ComponentCount(type)) {}

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
    }
}

BufferLayout::BufferLayout(std::initializer_list<BufferElement> layout) : elements(layout) {
    uint64_t offset = 0;
    for (auto& element : elements) {
        element.offset = offset;
        offset += element.Size();
        stride += element.Size();
    }
}

GPUVertexBuffer::GPUVertexBuffer(GPUDevice& device, BufferLayout layout, uint64_t vertexCount)
    : GPUBuffer(device, layout.Stride()*vertexCount, CopyDst | Vertex), Size(layout.Stride()*vertexCount) {
    uint32_t Location = 0;
    for (auto element : layout){
        WGPUVertexAttribute attribute;
        attribute.shaderLocation = Location++;
        attribute.offset = element.Offset();
        attribute.format = GetWGPUFormat(element.GetType());
        vertexAttribs.push_back(attribute);
    }

    vertexBufferLayout.arrayStride = layout.Stride();
    vertexBufferLayout.stepMode = WGPUVertexStepMode_Vertex;
    vertexBufferLayout.attributeCount = vertexAttribs.size();
    vertexBufferLayout.attributes = vertexAttribs.data();
}

WGPUVertexFormat GPUVertexBuffer::GetWGPUFormat(DataType type) {
    switch (type) {
        case DataType::Undefined : return WGPUVertexFormat_Undefined;
        case DataType::Uint8x2: return WGPUVertexFormat_Uint8x2;
        case DataType::Uint8x4: return WGPUVertexFormat_Uint8x4;
        case DataType::Int8x2: return WGPUVertexFormat_Sint8x2;
        case DataType::Int8x4: return WGPUVertexFormat_Sint8x4;
        case DataType::Unorm8x2: return WGPUVertexFormat_Unorm8x2;
        case DataType::Unorm8x4: return WGPUVertexFormat_Unorm8x4;
        case DataType::Norm8x2: return WGPUVertexFormat_Snorm8x2;
        case DataType::Norm8x4: return WGPUVertexFormat_Snorm8x4;
        case DataType::Uint16x2: return WGPUVertexFormat_Uint16x2;
        case DataType::Uint16x4: return WGPUVertexFormat_Uint16x4;
        case DataType::Int16x2: return WGPUVertexFormat_Sint16x2;
        case DataType::Int16x4: return WGPUVertexFormat_Sint16x4;
        case DataType::Unorm16x2: return WGPUVertexFormat_Unorm16x2;
        case DataType::Unorm16x4: return WGPUVertexFormat_Unorm16x4;
        case DataType::Norm16x2: return WGPUVertexFormat_Snorm16x2;
        case DataType::Norm16x4: return WGPUVertexFormat_Snorm16x4;
        case DataType::Float16x2: return WGPUVertexFormat_Float16x2;
        case DataType::Float16x4: return WGPUVertexFormat_Float16x4;
        case DataType::Float32: return WGPUVertexFormat_Float32;
        case DataType::Float32x2: return WGPUVertexFormat_Float32x2;
        case DataType::Float32x3: return WGPUVertexFormat_Float32x3;
        case DataType::Float32x4: return WGPUVertexFormat_Float32x4;
        case DataType::Uint32: return WGPUVertexFormat_Uint32;
        case DataType::Uint32x2: return WGPUVertexFormat_Uint32x2;
        case DataType::Uint32x3: return WGPUVertexFormat_Uint32x3;
        case DataType::Uint32x4: return WGPUVertexFormat_Uint32x4;
        case DataType::Int32: return WGPUVertexFormat_Sint32;
        case DataType::Int32x2: return WGPUVertexFormat_Sint32x2;
        case DataType::Int32x3: return WGPUVertexFormat_Sint32x3;
        case DataType::Int32x4: return WGPUVertexFormat_Sint32x4;
    }
    return WGPUVertexFormat_Undefined;
}
