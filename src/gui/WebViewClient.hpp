#pragma once

#include <include/cef_app.h>
#include <utility>

#include "WebViewRenderer.hpp"

class WebViewClient : public CefApp, public CefClient, public CefBrowserProcessHandler {
    IMPLEMENT_REFCOUNTING(WebViewClient);

public:
    explicit WebViewClient(CefRefPtr<WebViewRenderer> renderer) : renderer(std::move(renderer)){};

    WebViewClient(const WebViewClient &) = delete;
    const WebViewClient &operator=(const WebViewClient &) = delete;

    void OnBeforeCommandLineProcessing(const CefString &type, CefRefPtr<CefCommandLine> commandLine) override;

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

    CefRefPtr<CefRenderHandler> GetRenderHandler() override;

    CefRefPtr<CefClient> GetDefaultClient() override;

private:
    CefRefPtr<WebViewRenderer> renderer;
};
