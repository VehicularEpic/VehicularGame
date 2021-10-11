#include "WebViewEventHandler.hpp"

WebViewEventHandler::WebViewEventHandler(
        GLFWwindow *window, CefRefPtr<CefBrowser> browser, CefRefPtr<WebViewRenderer> webview)
    : browser(std::move(browser)), webview(std::move(webview)) {
    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, WebViewEventHandler::FramebufferSizeCallback);
}

void WebViewEventHandler::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    auto *eventHandler = reinterpret_cast<WebViewEventHandler *>(glfwGetWindowUserPointer(window));

    glViewport(0, 0, width, height);

    eventHandler->webview->SetSize(width, height);
    eventHandler->browser->GetHost()->WasResized();
}
