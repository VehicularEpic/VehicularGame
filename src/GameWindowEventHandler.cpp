#include "GameWindowEventHandler.hpp"

void GameWindowEventHandler::CallWindowCloseListeners(GLFWwindow *window) {
    auto handler = reinterpret_cast<GameWindowEventHandler *>(glfwGetWindowUserPointer(window));

    for (const WindowCloseListener &listener : handler->WindowCloseListeners)
        listener();
}

void GameWindowEventHandler::CallWindowSizeListeners(GLFWwindow *window, int width, int height) {
    auto handler = reinterpret_cast<GameWindowEventHandler *>(glfwGetWindowUserPointer(window));

    for (const WindowSizeListener &listener : handler->WindowSizeListeners)
        listener(width, height);
}

void GameWindowEventHandler::CallFramebufferSizeListeners(GLFWwindow *window, int width, int height) {
    auto handler = reinterpret_cast<GameWindowEventHandler *>(glfwGetWindowUserPointer(window));

    for (const FramebufferSizeListener &listener : handler->FramebufferSizeListeners)
        listener(width, height);
}

void GameWindowEventHandler::CallMouseMoveListeners(GLFWwindow *window, double xpos, double ypos) {
    auto handler = reinterpret_cast<GameWindowEventHandler *>(glfwGetWindowUserPointer(window));

    for (const MouseMoveListener &listener : handler->MouseMoveListeners)
        listener(xpos, ypos);
}

void GameWindowEventHandler::CallMouseEnterListeners(GLFWwindow *window, int entered) {
    if (!entered)
        return GameWindowEventHandler::CallMouseLeaveListeners(window);

    auto handler = reinterpret_cast<GameWindowEventHandler *>(glfwGetWindowUserPointer(window));

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    for (const MouseEnterListener &listener : handler->MouseEnterListeners)
        listener(xpos, ypos);
}

void GameWindowEventHandler::CallMouseLeaveListeners(GLFWwindow *window) {
    auto handler = reinterpret_cast<GameWindowEventHandler *>(glfwGetWindowUserPointer(window));

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    for (const MouseLeaveListener &listener : handler->MouseLeaveListeners)
        listener(xpos, ypos);
}

void GameWindowEventHandler::CallMouseDownListeners(GLFWwindow *window, int button, int action, int mods) {
    if (GLFW_RELEASE == action)
        return GameWindowEventHandler::CallMouseUpListeners(window, button, mods);

    auto handler = reinterpret_cast<GameWindowEventHandler *>(glfwGetWindowUserPointer(window));

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    for (const MouseDownListener &listener : handler->MouseDownListeners)
        listener(static_cast<MouseButton>(button), xpos, ypos);
}

void GameWindowEventHandler::CallMouseUpListeners(GLFWwindow *window, int button, int mods) {
    auto handler = reinterpret_cast<GameWindowEventHandler *>(glfwGetWindowUserPointer(window));

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    for (const MouseUpListener &listener : handler->MouseUpListeners)
        listener(static_cast<MouseButton>(button), xpos, ypos);
}

void GameWindowEventHandler::CallScrollListeners(GLFWwindow *window, double xoffset, double yoffset) {
    auto handler = reinterpret_cast<GameWindowEventHandler *>(glfwGetWindowUserPointer(window));

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    for (const ScrollListener &listener : handler->ScrollListeners)
        listener(xpos, ypos, xoffset, yoffset);
}

void GameWindowEventHandler::CallTextListeners(GLFWwindow *window, unsigned int codepoint) {
    auto handler = reinterpret_cast<GameWindowEventHandler *>(glfwGetWindowUserPointer(window));

    for (const TextListener &listener : handler->TextListeners)
        listener(codepoint);
}
