#pragma once

#include <functional>
#include <vector>

#include "GLFW.hpp"

enum MouseButton : int {

    LEFT = GLFW_MOUSE_BUTTON_LEFT,
    RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
    MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,

};

using WindowCloseListener = std::function<void()>;

using SizeListener = std::function<void(int width, int height)>;
using WindowSizeListener = SizeListener;
using FramebufferSizeListener = SizeListener;

using MouseListener = std::function<void(double xpos, double ypos)>;
using MouseMoveListener = MouseListener;
using MouseEnterListener = MouseListener;
using MouseLeaveListener = MouseListener;

using MouseButtonListener = std::function<void(MouseButton button, double xpos, double ypos)>;
using MouseDownListener = MouseButtonListener;
using MouseUpListener = MouseButtonListener;

using ScrollListener = std::function<void(double xpos, double ypos, double xoffset, double yoffset)>;
using TextListener = std::function<void(unsigned int codepoint)>;

#define IMPLEMENT_LISTENER(type, ...)                           \
private:                                                        \
    std::vector<type> type##s;                                  \
    static void Call##type##s(GLFWwindow *window, __VA_ARGS__); \
                                                                \
public:                                                         \
    void Add##type(const type &listener) {                      \
        type##s.push_back(listener);                            \
    }

class GameWindowEventHandler {
    IMPLEMENT_LISTENER(WindowCloseListener);
    IMPLEMENT_LISTENER(WindowSizeListener, int width, int height);
    IMPLEMENT_LISTENER(FramebufferSizeListener, int width, int height);
    IMPLEMENT_LISTENER(MouseMoveListener, double xpos, double ypos);
    IMPLEMENT_LISTENER(MouseEnterListener, int entered);
    IMPLEMENT_LISTENER(MouseLeaveListener);
    IMPLEMENT_LISTENER(MouseDownListener, int button, int action, int mods);
    IMPLEMENT_LISTENER(MouseUpListener, int button, int mods);
    IMPLEMENT_LISTENER(ScrollListener, double xoffset, double yoffset);
    IMPLEMENT_LISTENER(TextListener, unsigned int codepoint)
public:
    explicit GameWindowEventHandler(GLFWwindow *window) {
        glfwSetWindowUserPointer(window, this);

        glfwSetWindowCloseCallback(window, GameWindowEventHandler::CallWindowCloseListeners);
        glfwSetWindowSizeCallback(window, GameWindowEventHandler::CallWindowSizeListeners);
        glfwSetFramebufferSizeCallback(window, GameWindowEventHandler::CallFramebufferSizeListeners);
        glfwSetCursorPosCallback(window, GameWindowEventHandler::CallMouseMoveListeners);
        glfwSetCursorEnterCallback(window, GameWindowEventHandler::CallMouseEnterListeners);
        glfwSetMouseButtonCallback(window, GameWindowEventHandler::CallMouseDownListeners);
        glfwSetScrollCallback(window, GameWindowEventHandler::CallScrollListeners);
        glfwSetCharCallback(window, GameWindowEventHandler::CallTextListeners);
    }
};
