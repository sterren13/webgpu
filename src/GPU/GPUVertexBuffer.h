//
// Created by arno on 12/07/23.
//

#ifndef TESTWEBGPU_GPUVERTEXBUFFER_H
#define TESTWEBGPU_GPUVERTEXBUFFER_H
#include "GPUBuffer.h"
#include "GPUDevice.h"
#include <string>
#include <initializer_list>
#include <vector>

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
    Force32
};

class BufferElement {
public:
    BufferElement() = default;
    BufferElement(DataType type, const std::string& name);

    inline void SetName(std::string& name) {Name = name;}
    inline void SetType(DataType type) {Type = type; Size = Get_DataTypeSize(type);}

    [[nodiscard]] inline std::string GetName() const{return Name;}
    [[nodiscard]] inline DataType GetType() const{return Type;}
    [[nodiscard]] inline uint64_t GetSize() const{return Size;}
    [[nodiscard]] inline uint64_t GetComponentCount() const{return ComponentCount;}
private:
    static const uint64_t Get_DataTypeSize(DataType type);
    static const uint64_t Get_ComponentCount(DataType type);
private:
    std::string Name = "";
    DataType Type = DataType::Undefined;
    uint64_t Size = 0;
    uint64_t ComponentCount = 0;
};

class BufferLayout {
public:
    BufferLayout() = default;
    BufferLayout(std::initializer_list<BufferElement> elements);

    [[nodiscard]] inline size_t GetStride() const {return Stride;}
    void PusheLements(std::initializer_list<BufferElement> elements);

private:
    void Calculate();
    std::vector<BufferElement> BufferElements;
    std::vector<WGPUVertexAttribute> BufferAttributes;
    uint64_t Stride = 0;
};

class GPUVertexBuffer : public GPUBuffer {
public:
    GPUVertexBuffer(GPUDevice& device, uint64_t VertexCount);

private:
    friend class GPURenderPass;
    friend class GPURenderPipeline;

    WGPUVertexAttribute vertexAttrib;
    WGPUVertexBufferLayout vertexBufferLayout{};
};

#endif //TESTWEBGPU_GPUVERTEXBUFFER_H
