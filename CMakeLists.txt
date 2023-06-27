cmake_minimum_required(VERSION 3.25)
project(
        testWebGPU
        VERSION 0.1.0
        LANGUAGES CXX C
)

add_executable(App src/main.cpp)

set_target_properties(App PROPERTIES
    CXX_STANDARD 17
    COMPILE_WARNING_AS_ERROR ON
)

if (MSVC)
    target_compile_options(App PRIVATE /W4)
elseif(XCODE)
    set_target_properties(App PROPERTIES
        XCODE_GENERATE_SCHEME ON
        XCODE_SCHEME_ENABLE_GPU_FRAME_CAPTURE_MODE "Metal")
else()
    target_compile_options(App PRIVATE -Wall -Wextra -pedantic)
endif()