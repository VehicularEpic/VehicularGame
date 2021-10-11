#include "GameWindow.hpp"

static void errorCallback(int error, const char *description) {
    fprintf(stderr, "GLFW Error: %s (%d)\n", description, error);
}

GameWindow::GameWindow(const std::string &name, int width, int height, bool vsync)
    : width(width), height(height) {
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

    win = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    if (!win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetInputMode(win, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    glfwMakeContextCurrent(win);
    gladLoadGL(glfwGetProcAddress);

    glfwSwapInterval(vsync);
}
