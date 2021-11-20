#include "WebViewClient.hpp"

CefRefPtr<CefRenderHandler> WebViewClient::GetRenderHandler() {
    return this->renderer;
}

bool WebViewClient::OnProcessMessageReceived(
        CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefProcessId source_process,
        CefRefPtr<CefProcessMessage> message) {
    Emit(message->GetName(), message->GetArgumentList());
    return true;
}

void WebViewClient::Emit(
        const std::string &event,
        const CefRefPtr<CefListValue> &arguments) {
    auto range = events.equal_range(event);

    for (auto it = range.first; it != range.second; it++) {
        JSCallback &callback = it->second;
        callback(arguments);
    }
}

void WebViewClient::On(
        const std::string &event,
        const JSCallback &callback) {
    events.insert(std::make_pair(event, callback));
}
