#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <string>

class Window {
public:
    explicit Window(const std::string &, int, int, bool);

    void show();

    void update();

    bool active();

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

private:
    GLFWwindow *win;

    int width;
    int height;
};
