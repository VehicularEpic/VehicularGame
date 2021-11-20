#pragma once

#include <include/cef_client.h>

#include <functional>
#include <map>
#include <utility>

#include "WebViewRenderer.hpp"

using JSCallback = std::function<void(CefRefPtr<CefListValue>)>;

class WebViewClient : public CefClient {
    IMPLEMENT_REFCOUNTING(WebViewClient);

public:
    explicit WebViewClient(CefRefPtr<WebViewRenderer> renderer)
        : renderer(std::move(renderer)) {}

    WebViewClient(const WebViewClient &) = delete;
    const WebViewClient &operator=(const WebViewClient &) = delete;

    CefRefPtr<CefRenderHandler> GetRenderHandler() override;

    bool OnProcessMessageReceived(
            CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefProcessId source_process,
            CefRefPtr<CefProcessMessage> message) override;

    void Emit(
            const std::string &event,
            const CefRefPtr<CefListValue> &arguments);

    void On(
            const std::string &event,
            const JSCallback &callback);

private:
    CefRefPtr<WebViewRenderer> renderer;

    std::multimap<std::string, JSCallback> events;
};
