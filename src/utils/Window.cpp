#include <glad/gl.h>
#include "Window.h"

Window::Window(int width, int height, const std::string &title) : m_LastX(width/2.0f), m_LastY(height/2.0f){
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(m_Window, this); // needed for mousecallback
    glfwSetCursorPosCallback(m_Window, MouseCallback);

    gladLoadGL(glfwGetProcAddress);
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(m_Window);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(m_Window);
}

void Window::PollEvents() {
    glfwPollEvents();
}

bool Window::IsKeyPressed(int key) {
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

void Window::Close() {
    glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

float Window::GetMouseOffsetX() {
    float offset = m_OffsetX;
    m_OffsetX = 0.0f; // Reset per frame
    return offset;
}

float Window::GetMouseOffsetY() {
    float offset = m_OffsetY;
    m_OffsetY = 0.0f; // Reset per frame
    return offset;
}

void Window::MouseCallback(GLFWwindow *window, double xposIn, double yposIn) {
    auto *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (self->m_FirstMouse) {
        self->m_LastX = xpos;
        self->m_LastY = ypos;
        self->m_FirstMouse = false;
    }

    self->m_OffsetX += xpos - self->m_LastX;
    self->m_OffsetY += self->m_LastY - ypos; // Reversed since Y-coords go bottom-to-top

    self->m_LastX = xpos;
    self->m_LastY = ypos;
}


