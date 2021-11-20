#pragma once

#include <include/cef_scheme.h>

class WebViewSchemeHandler : public CefSchemeHandlerFactory {
    IMPLEMENT_REFCOUNTING(WebViewSchemeHandler);

public:
    WebViewSchemeHandler() = default;

    WebViewSchemeHandler(const WebViewSchemeHandler &) = delete;
    const WebViewSchemeHandler &operator=(const WebViewSchemeHandler &) = delete;

    CefRefPtr<CefResourceHandler> Create(
            CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
            const CefString &scheme_name, CefRefPtr<CefRequest> request) override;
};
