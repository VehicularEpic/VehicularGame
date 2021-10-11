#pragma once

#include <string>

#include "GLFW.hpp"
#include <glad/gl.h>

class Window {
public:
    Window(const std::string &name, int width, int height, bool vsync);

    int GetWidth() const {
        return width;
    }

    int GetHeight() const {
        return height;
    }

    GLFWwindow *GetWindow() const {
        return win;
    }

private:
    GLFWwindow *win;

    int width;
    int height;
};
