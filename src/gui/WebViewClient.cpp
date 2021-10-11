#include "WebViewClient.hpp"

void WebViewClient::OnBeforeCommandLineProcessing(const CefString &type, CefRefPtr<CefCommandLine> commandLine) {
    commandLine->AppendSwitchWithValue("autoplay-policy", "no-user-gesture-required");
}

CefRefPtr<CefBrowserProcessHandler> WebViewClient::GetBrowserProcessHandler() {
    return this;
}

CefRefPtr<CefRenderHandler> WebViewClient::GetRenderHandler() {
    return renderer;
}

CefRefPtr<CefClient> WebViewClient::GetDefaultClient() {
    return this;
}
