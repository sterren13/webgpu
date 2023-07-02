cmake_minimum_required(VERSION 3.25)
project(
        testWebGPU
        VERSION 0.1.0
        LANGUAGES CXX C
)

add_subdirectory(lib/glfw)
add_subdirectory(lib/webgpu)

add_executable(testWebGPU src/main.cpp "src/webgpu-utils.h" src/webgpu-utils.cpp src/webgpu-release.h src/glfw3webgpu.h src/glfw3webgpu.c)
include_directories(src lib/webgpu/Include)

target_link_libraries(testWebGPU PRIVATE glfw webgpu)

set_target_properties(testWebGPU PROPERTIES
    CXX_STANDARD 17
    COMPILE_WARNING_AS_ERROR ON
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

target_copy_webgpu_binaries(testWebGPU)