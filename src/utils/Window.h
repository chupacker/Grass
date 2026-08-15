#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string &title);

    ~Window();

    bool ShouldClose();

    void SwapBuffers();

    void PollEvents();

    bool IsKeyPressed(int key);

    void Close();

    float GetMouseOffsetX();

    float GetMouseOffsetY();

private:
    GLFWwindow *m_Window;


    static void MouseCallback(GLFWwindow *window, double xpos, double ypos);
    float m_LastX, m_LastY;
    float m_OffsetX = 0.0f, m_OffsetY = 0.0f;
    bool m_FirstMouse = true;
};
