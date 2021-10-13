#include "WebViewClient.hpp"

CefRefPtr<CefRenderHandler> WebViewClient::GetRenderHandler() {
    return this->renderer;
}
