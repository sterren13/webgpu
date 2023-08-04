//
// Created by sterr on 3/07/2023.
//

#include "GPUDevice.h"
#include <webgpu/wgpu.h>
#include <iostream>
#include <vector>
#include <cassert>

void setDefault(WGPULimits &limits) {
    limits.maxTextureDimension1D = 0;
    limits.maxTextureDimension2D = 0;
    limits.maxTextureDimension3D = 0;
    limits.maxTextureArrayLayers = 0;
    limits.maxBindGroups = 0;
    limits.maxBindingsPerBindGroup = 0;
    limits.maxDynamicUniformBuffersPerPipelineLayout = 0;
    limits.maxDynamicStorageBuffersPerPipelineLayout = 0;
    limits.maxSampledTexturesPerShaderStage = 0;
    limits.maxSamplersPerShaderStage = 0;
    limits.maxStorageBuffersPerShaderStage = 0;
    limits.maxStorageTexturesPerShaderStage = 0;
    limits.maxUniformBuffersPerShaderStage = 0;
    limits.maxUniformBufferBindingSize = 0;
    limits.maxStorageBufferBindingSize = 0;
    limits.minUniformBufferOffsetAlignment = 0;
    limits.minStorageBufferOffsetAlignment = 0;
    limits.maxVertexBuffers = 0;
    limits.maxBufferSize = 0;
    limits.maxVertexAttributes = 0;
    limits.maxVertexBufferArrayStride = 0;
    limits.maxInterStageShaderComponents = 0;
    limits.maxInterStageShaderVariables = 0;
    limits.maxColorAttachments = 0;
    limits.maxColorAttachmentBytesPerSample = 0;
    limits.maxComputeWorkgroupStorageSize = 0;
    limits.maxComputeInvocationsPerWorkgroup = 0;
    limits.maxComputeWorkgroupSizeX = 0;
    limits.maxComputeWorkgroupSizeY = 0;
    limits.maxComputeWorkgroupSizeZ = 0;
    limits.maxComputeWorkgroupsPerDimension = 0;
}

GPUDevice::GPUDevice(GPUAdapter& adapter) {
    descriptor = {
            .nextInChain = nullptr,
            .label = "My Device",
            .requiredFeaturesCount = 0,
            .requiredLimits = nullptr,
    };

    setDefault(requiredLimits.limits);
    // vertex buffer
    requiredLimits.limits.maxVertexAttributes = 2;
    requiredLimits.limits.maxVertexBuffers = 1;
    requiredLimits.limits.maxBufferSize = 6 * 5 * sizeof(float);
    requiredLimits.limits.maxVertexBufferArrayStride = 5 * sizeof(float);
    // uniform buffers
    requiredLimits.limits.minStorageBufferOffsetAlignment = adapter.limits.limits.minStorageBufferOffsetAlignment;
    requiredLimits.limits.minUniformBufferOffsetAlignment = adapter.limits.limits.minUniformBufferOffsetAlignment;
    requiredLimits.limits.maxInterStageShaderComponents = 6;
    requiredLimits.limits.maxBindGroups = 1;
    requiredLimits.limits.maxUniformBuffersPerShaderStage = 1;
    requiredLimits.limits.maxUniformBufferBindingSize = 16 * 4 * sizeof(float);
    // textures
    requiredLimits.limits.maxSampledTexturesPerShaderStage = 1;
    requiredLimits.limits.maxTextureDimension1D = 480;
    requiredLimits.limits.maxTextureDimension2D = 640;
    requiredLimits.limits.maxTextureArrayLayers = 1;
    descriptor.requiredLimits = &requiredLimits;

    struct UserData {
        WGPUDevice device = nullptr;
        bool requestEnded = false;
    };
    UserData userData;

    auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status, WGPUDevice device, char const * message, void * pUserData) {
        UserData& userData = *reinterpret_cast<UserData*>(pUserData);
        if (status == WGPURequestDeviceStatus_Success) {
            userData.device = device;
        } else {
            std::cout << "Could not get WebGPU adapter: " << message << std::endl;
        }
        userData.requestEnded = true;
    };

    wgpuAdapterRequestDevice(
            adapter.adapter,
            &descriptor,
            onDeviceRequestEnded,
            (void*)&userData
    );

    assert(userData.requestEnded);
    device = userData.device;
    wgpuDeviceSetUncapturedErrorCallback(device, onDeviceError, nullptr);
}

GPUDevice::~GPUDevice() {
    wgpuDeviceRelease(device);
}

void GPUDevice::onDeviceError(WGPUErrorType type, const char *massage, void *pUserData) {
    std::cerr << "Uncaptured device error: type " << type;
    if (massage) std::cerr << "(" << massage << ")";
    std::cerr <<"\n";
}

void GPUDevice::inspect() {
    std::vector<WGPUFeatureName> features;
    size_t featureCount = wgpuDeviceEnumerateFeatures(device, nullptr);
    features.resize(featureCount);
    wgpuDeviceEnumerateFeatures(device, features.data());

    std::cout << "Device features:" << std::endl;
    for (auto f : features) {
        std::cout << " - " << f << std::endl;
    }

    WGPUSupportedLimits limits = {};
    limits.nextInChain = nullptr;
    bool success = wgpuDeviceGetLimits(device, &limits);
    if (success) {
        std::cout << "Device limits:" << std::endl;
        std::cout << " - maxTextureDimension1D: " << limits.limits.maxTextureDimension1D << std::endl;
        std::cout << " - maxTextureDimension2D: " << limits.limits.maxTextureDimension2D << std::endl;
        std::cout << " - maxTextureDimension3D: " << limits.limits.maxTextureDimension3D << std::endl;
        std::cout << " - maxTextureArrayLayers: " << limits.limits.maxTextureArrayLayers << std::endl;
        std::cout << " - maxBindGroups: " << limits.limits.maxBindGroups << std::endl;
        std::cout << " - maxDynamicUniformBuffersPerPipelineLayout: " << limits.limits.maxDynamicUniformBuffersPerPipelineLayout << std::endl;
        std::cout << " - maxDynamicStorageBuffersPerPipelineLayout: " << limits.limits.maxDynamicStorageBuffersPerPipelineLayout << std::endl;
        std::cout << " - maxSampledTexturesPerShaderStage: " << limits.limits.maxSampledTexturesPerShaderStage << std::endl;
        std::cout << " - maxSamplersPerShaderStage: " << limits.limits.maxSamplersPerShaderStage << std::endl;
        std::cout << " - maxStorageBuffersPerShaderStage: " << limits.limits.maxStorageBuffersPerShaderStage << std::endl;
        std::cout << " - maxStorageTexturesPerShaderStage: " << limits.limits.maxStorageTexturesPerShaderStage << std::endl;
        std::cout << " - maxUniformBuffersPerShaderStage: " << limits.limits.maxUniformBuffersPerShaderStage << std::endl;
        std::cout << " - maxUniformBufferBindingSize: " << limits.limits.maxUniformBufferBindingSize << std::endl;
        std::cout << " - maxStorageBufferBindingSize: " << limits.limits.maxStorageBufferBindingSize << std::endl;
        std::cout << " - minUniformBufferOffsetAlignment: " << limits.limits.minUniformBufferOffsetAlignment << std::endl;
        std::cout << " - minStorageBufferOffsetAlignment: " << limits.limits.minStorageBufferOffsetAlignment << std::endl;
        std::cout << " - maxVertexBuffers: " << limits.limits.maxVertexBuffers << std::endl;
        std::cout << " - maxVertexAttributes: " << limits.limits.maxVertexAttributes << std::endl;
        std::cout << " - maxVertexBufferArrayStride: " << limits.limits.maxVertexBufferArrayStride << std::endl;
        std::cout << " - maxInterStageShaderComponents: " << limits.limits.maxInterStageShaderComponents << std::endl;
        std::cout << " - maxComputeWorkgroupStorageSize: " << limits.limits.maxComputeWorkgroupStorageSize << std::endl;
        std::cout << " - maxComputeInvocationsPerWorkgroup: " << limits.limits.maxComputeInvocationsPerWorkgroup << std::endl;
        std::cout << " - maxComputeWorkgroupSizeX: " << limits.limits.maxComputeWorkgroupSizeX << std::endl;
        std::cout << " - maxComputeWorkgroupSizeY: " << limits.limits.maxComputeWorkgroupSizeY << std::endl;
        std::cout << " - maxComputeWorkgroupSizeZ: " << limits.limits.maxComputeWorkgroupSizeZ << std::endl;
        std::cout << " - maxComputeWorkgroupsPerDimension: " << limits.limits.maxComputeWorkgroupsPerDimension << std::endl;
    }
}
