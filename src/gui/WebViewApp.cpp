#include "WebViewApp.hpp"

CefRefPtr<CefBrowserProcessHandler> WebViewApp::GetBrowserProcessHandler() {
    return this;
}

CefRefPtr<CefClient> WebViewApp::GetDefaultClient() {
    return this->client;
}
