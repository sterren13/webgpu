//
// Created by sterr on 1/07/2023.
//

#ifndef TESTWEBGPU_WINDOW_H
#define TESTWEBGPU_WINDOW_H
//#define GLFW_PLATFORM GLFW_PLATFORM_WAYLAND
#include "GLFW/glfw3.h"

class window {
public:
    window(const char* title, size_t width, size_t height, bool fullscreen, bool vsync);
    ~window();
    bool Update();
    void SetTitle();
    void SetEventCallbacks();

    // window properties
    size_t GetWidth() const;
    size_t GetHeight() const;
    bool IsFullScreen() const;
    bool IsVSync() const;

    // set window properties
    void SetDimensions(size_t width, size_t height);
    void SetFullScreen(bool fullscreen);
    void SetVSync(bool vsync);

    void* GetNativeWindow() const;

private:
    static void GLFW_ErrorCallback(int error, const char* description);
    static void GLFW_ResizedCallback(GLFWwindow* window, int width, int height);
    static void GLFW_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void GLFW_MouseButtonCallback(GLFWwindow *wnd, int button, int state, int mods);
    static void GLFW_CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void GLFW_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void GLFW_CharCallback(GLFWwindow* window, unsigned int codepoint);
    static void GLFW_JoystickCallback(int joy, int event);

    bool _CreateWindow(const char* title, uint32_t width, uint32_t height);

private:
    friend class GPUSurface;
    GLFWwindow* m_Window;
    bool m_FullScreen, m_VSync;
};


#endif //TESTWEBGPU_WINDOW_H
