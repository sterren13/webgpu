//
// Created by sterr on 1/07/2023.
//

#include "window.h"
#include <iostream>

window::window(const char* title, size_t width, size_t height, bool fullscreen, bool vsync):
    m_FullScreen(fullscreen), m_VSync(vsync){
    if (!_CreateWindow(title, width, height)) return;
}

bool window::_CreateWindow(const char *title, uint32_t width, uint32_t height) {
    if (!glfwInit()) {
        std::cerr << "[Error] Could not initialize GLFW!\n";
        return false;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!m_Window) {
        std::cerr << "[Error] Could not open window! \n";
        return false;
    }
    return true;
}

window::~window() {
    if (m_Window)
        glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool window::Update() {
    glfwPollEvents();
    return glfwWindowShouldClose(m_Window);
}

void window::SetTitle() {

}

void window::SetEventCallbacks() {

}

size_t window::GetWidth() const {
    return 0;
}

size_t window::GetHeight() const {
    return 0;
}

bool window::IsFullScreen() const {
    return false;
}

bool window::IsVSync() const {
    return false;
}

void window::SetDimensions(size_t width, size_t height) {

}

void window::SetFullScreen(bool fullscreen) {

}

void window::SetVSync(bool vsync) {

}

void *window::GetNativeWindow() const {
    return nullptr;
}

void window::GLFW_ErrorCallback(int error, const char *description) {
    std::cerr << description << "\n";
}

void window::GLFW_ResizedCallback(GLFWwindow *window, int width, int height) {

}

void window::GLFW_KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

}

void window::GLFW_MouseButtonCallback(GLFWwindow *wnd, int button, int state, int mods) {

}

void window::GLFW_CursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {

}

void window::GLFW_ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {

}

void window::GLFW_CharCallback(GLFWwindow *window, unsigned int codepoint) {

}

void window::GLFW_JoystickCallback(int joy, int event) {

}