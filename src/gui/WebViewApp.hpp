#pragma once

#include <utility>

#include "../cef/BasicApp.hpp"
#include "WebViewClient.hpp"

class WebViewApp : public BasicApp, public CefBrowserProcessHandler {
    IMPLEMENT_REFCOUNTING(WebViewApp);

public:
    explicit WebViewApp(CefRefPtr<WebViewClient> client)
        : client(std::move(client)) {}

    WebViewApp(const WebViewApp &) = delete;
    const WebViewApp &operator=(const WebViewApp &) = delete;

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

    CefRefPtr<CefClient> GetDefaultClient() override;

    void OnContextInitialized() override;

private:
    CefRefPtr<WebViewClient> client;
};
