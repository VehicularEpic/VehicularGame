#pragma once

#include <include/cef_browser.h>
#include <utility>

#include "../GLFW.hpp"
#include "WebViewRenderer.hpp"

class WebViewEventHandler {
public:
    WebViewEventHandler(GLFWwindow *window, CefRefPtr<CefBrowser> browser, CefRefPtr<WebViewRenderer> webview);

private:
    CefRefPtr<CefBrowser> browser;
    CefRefPtr<WebViewRenderer> webview;

    static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
};
