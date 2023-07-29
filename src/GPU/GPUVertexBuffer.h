//
// Created by arno on 12/07/23.
//

#ifndef TESTWEBGPU_GPUVERTEXBUFFER_H
#define TESTWEBGPU_GPUVERTEXBUFFER_H
#include "GPUBuffer.h"
#include "GPUDevice.h"
#include <string>
#include <initializer_list>

enum class DataType {
//  vec 1       vec 2       vec 3       vec 4
    Undefined,
                Uint8x2,                Uint8x4,
                Int8x2,                 Int8x4,
                Unorm8x2,               Unorm8x4,
                Norm8x2,                Norm8x4,
                Uint16x2,               Uint16x4,
                Int16x2,                Int16x4,
                Unorm16x2,              Unorm16x4,
                Norm16x2,               Norm16x4,
                Float16x2,              Float16x4,
    Float32,    Float32x2,  Float32x3,  Float32x4,
    Uint32,     Uint32x2,   Uint32x3,   Uint32x4,
    Int32,      Int32x2,    Int32x3,    Int32x4,
};

class BufferElement {
public:
    BufferElement(DataType type, const std::string& name);

    inline void SetName(std::string& name) {Name = name;}
    inline void SetType(DataType type) {Type = type; size = Get_DataTypeSize(type);}

    [[nodiscard]] inline std::string GetName() const{return Name;}
    [[nodiscard]] inline DataType GetType() const{return Type;}
    [[nodiscard]] inline uint64_t Size() const{return size;}
    [[nodiscard]] inline uint64_t GetComponentCount() const{return ComponentCount;}
    [[nodiscard]] inline uint64_t Offset() const {return offset;}
private:
    static const uint64_t Get_DataTypeSize(DataType type);
    static const uint64_t Get_ComponentCount(DataType type);
private:
    friend class BufferLayout;
private:
    std::string Name = "";
    DataType Type = DataType::Undefined;
    uint64_t size = 0;
    uint64_t ComponentCount = 0;
    uint64_t offset = 0;
};

class BufferLayout {
public:
    BufferLayout(std::initializer_list<BufferElement> layout);
    [[nodiscard]] inline uint64_t Stride() const {return stride;}

    std::vector<BufferElement>::iterator begin() {return elements.begin();}
    std::vector<BufferElement>::iterator end() {return elements.end();}
    [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const {return elements.begin();}
    [[nodiscard]] std::vector<BufferElement>::const_iterator end() const {return elements.end();}
private:
    uint64_t stride = 0;
    std::vector<BufferElement> elements;
};

class GPUVertexBuffer : public GPUBuffer {
public:
    GPUVertexBuffer(GPUDevice& device, BufferLayout layout, uint64_t vertexCount);

private:
    static WGPUVertexFormat GetWGPUFormat(DataType type);

private:
    friend class GPURenderPass;
    friend class GPURenderPipeline;

private:
    std::vector<WGPUVertexAttribute> vertexAttribs;
    WGPUVertexBufferLayout vertexBufferLayout{};
};

#endif //TESTWEBGPU_GPUVERTEXBUFFER_H
