#include "WebViewApp.hpp"
#include "WebViewSchemeHandler.hpp"

CefRefPtr<CefBrowserProcessHandler> WebViewApp::GetBrowserProcessHandler() {
    return this;
}

CefRefPtr<CefClient> WebViewApp::GetDefaultClient() {
    return this->client;
}

void WebViewApp::OnContextInitialized() {
    CefRegisterSchemeHandlerFactory("webview", "client", new WebViewSchemeHandler());
}
