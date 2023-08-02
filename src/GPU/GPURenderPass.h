//
// Created by sterr on 3/07/2023.
//

#ifndef TESTWEBGPU_GPURENDERPASS_H
#define TESTWEBGPU_GPURENDERPASS_H
#include <webgpu/webgpu.h>
#include "GPURenderPipeline.h"
#include "GPUVertexBuffer.h"
#include "GPUIndexBuffer.h"

/**
 * @class GPURenderPass
 *
 * @brief Represents a GPU render pass.
 *
 * This class encapsulates a GPU render pass, which is used to define and
 * execute a sequence of rendering operations on a render target.
 *
 */

class GPURenderPass {
public:
    /**
 * @class GPURenderPass
 *
 * @brief Represents a GPU render pass.
 *
 * This class encapsulates a GPU render pass, which is used to define and
 * execute a sequence of rendering operations on a render target.
 *
 */

    GPURenderPass(WGPURenderPassEncoder e);

    /**
 * @brief Sets the GPU render pipeline for rendering.
 *
 * This method sets the GPU render pipeline to be used for rendering.
 *
 * @param pipeline The GPU render pipeline to set.
 */

    void SetPipeline(GPURenderPipeline& pipeline);

    /**
 * @brief Binds a vertex buffer to the specified slot in the GPU
 *
 * This function binds a vertex buffer to the specified slot in the GPU. The vertex buffer
 * data will be used during rendering operations.
 *
 * @param slot The slot in the GPU where the vertex buffer will be bound
 * @param buffer A reference to the GPUVertexBuffer object representing the vertex buffer
 * @param offset The offset to the start of data within the vertex buffer
 */

    void SetVertexBuffer(uint32_t slot, GPUVertexBuffer &buffer, uint64_t offset);

    /**
 * \fn void SetIndexBuffer(GPUIndexBuffer& indexBuffer, uint64_t offset)
 * \ingroup Graphics
 * \brief Sets the index buffer for rendering.
 *
 * This function sets the specified GPUIndexBuffer as the current index buffer for rendering.
 * The index buffer defines the list of indices used to determine the order at which the vertices are rendered.
 * The offset parameter specifies the starting position within the index buffer where rendering should begin.
 *
 * \param indexBuffer The GPUIndexBuffer to be used as the current index buffer.
 * \param offset The offset position within the index buffer where rendering should start.
 *
 * \see GPUIndexBuffer
 */

    void SetIndexBuffer(GPUIndexBuffer& indexBuffer, uint64_t offset);

    /**
 * @class Draw
 * @brief Represents a Draw call in a rendering pipeline.
 *
 * The Draw class encapsulates the parameters required to perform a draw call.
 */

    void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

    /**
 * @brief Draws indexed primitives.
 *
 * This function is used to draw primitives represented by indexed vertices.
 * It takes the number of indices to be rendered and the number of instances to be rendered.
 * It also takes the first index and the first instance to be used during rendering.
 *
 * @param IndexCount       The number of indices to be rendered.
 * @param InstanceCount    The number of instances to be rendered.
 * @param FirstIndex       The index of the first primitive to be rendered.
 * @param FirstInstance    The instance ID of the first instance to be rendered.
 *
 * @note This function assumes that indexed vertices have already been specified and bound.
 *       Make sure to set up the vertex buffers and index buffer correctly before calling this function.
 *
 * @see SetVertexBuffers()
 * @see SetIndexBuffer()
 */

    void DrawIndexed(uint64_t IndexCount, uint64_t InstanceCount, uint64_t FirstIndex, uint64_t FirstInstance);

    //TODO void DrawIndirect();
    //TODO void DrawIndexedIndirect();
    //TODO void SetBindGroup();
    //TODO void PushDebugGroup();
    //TODO void PopDebugGroup();
    //TODO void InsertDebugMarker();
    //TODO void SetViewport();
    //TODO void SetScissorRect();
    //TODO void SetBlendConstant();
    //TODO void SetStencilReference();
    //TODO void BeginOcclusionQuery();

    void EndRenderPass();
private:
    WGPURenderPassEncoder encoder;
};

#endif //TESTWEBGPU_GPURENDERPASS_H
