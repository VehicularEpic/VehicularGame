#include "Window.hpp"

static void errorCallback(int error, const char *description) {
    fprintf(stderr, "GLFW Error: %s (%d)\n", description, error);
}

Window::Window(const std::string &title, int width, int height, bool vsync) : width(width), height(height) {
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#if defined(OS_MAC)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(win, this);
    glfwSetInputMode(win, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    glfwMakeContextCurrent(win);
    gladLoadGL(glfwGetProcAddress);

    glfwSwapInterval(vsync);
}

void Window::show() {
    glfwMaximizeWindow(win);
    glfwShowWindow(win);
}

void Window::update() {
    glfwSwapBuffers(win);
    glfwPollEvents();
}

bool Window::active() {
    return !glfwWindowShouldClose(win);
}
