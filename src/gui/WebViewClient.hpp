#pragma once

#include <include/cef_client.h>

#include <utility>

#include "WebViewRenderer.hpp"

class WebViewClient : public CefClient {
    IMPLEMENT_REFCOUNTING(WebViewClient);

public:
    explicit WebViewClient(CefRefPtr<WebViewRenderer> renderer)
        : renderer(std::move(renderer)) {}

    WebViewClient(const WebViewClient &) = delete;
    const WebViewClient &operator=(const WebViewClient &) = delete;

    CefRefPtr<CefRenderHandler> GetRenderHandler() override;

private:
    CefRefPtr<WebViewRenderer> renderer;
};
