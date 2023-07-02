cmake_minimum_required(VERSION 3.25)
project(
        testWebGPU
        VERSION 0.1.0
        LANGUAGES CXX C
)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_WAYLAND ON)
set(GLFW_BUILD_X11 OFF)
add_subdirectory(lib/glfw)
add_subdirectory(lib/webgpu)

add_executable(testWebGPU src/main.cpp src/GPU/GPUAdapter.cpp src/window.cpp src/GPU/GPUSurface.cpp src/GPU/GPUSurface.h src/GPU/GPUInstance.cpp src/GPU/GPUInstance.h)
include_directories(src lib/webgpu/Include)

target_link_libraries(testWebGPU PRIVATE glfw webgpu)

set_target_properties(testWebGPU PROPERTIES
    CXX_STANDARD 20
    #COMPILE_WARNING_AS_ERROR ON
)

if (MSVC)
    target_compile_options(testWebGPU PRIVATE /W4)
elseif(XCODE)
    set_target_properties(testWebGPU PROPERTIES
        XCODE_GENERATE_SCHEME ON
        XCODE_SCHEME_ENABLE_GPU_FRAME_CAPTURE_MODE "Metal")
else()
    target_compile_options(testWebGPU PRIVATE -Wall -Wextra -pedantic)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_copy_webgpu_binaries(testWebGPU)
endif()