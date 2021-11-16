#pragma once

#include "BasicApp.hpp"

class RenderProcess : public BasicApp, public CefRenderProcessHandler, public CefV8Handler {
    IMPLEMENT_REFCOUNTING(RenderProcess);

public:
    RenderProcess() = default;

    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override {
        return this;
    }

    void OnContextCreated(
            CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefV8Context> context) override;

    bool Execute(
            const CefString &name,
            CefRefPtr<CefV8Value> object,
            const CefV8ValueList &arguments,
            CefRefPtr<CefV8Value> &retval,
            CefString &exception) override;
};
