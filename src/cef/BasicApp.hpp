#pragma once

#include <include/cef_app.h>

class BasicApp : public CefApp {
    IMPLEMENT_REFCOUNTING(BasicApp);

public:
    BasicApp() = default;

    BasicApp(const BasicApp &) = delete;
    const BasicApp &operator=(const BasicApp &) = delete;

    void OnBeforeCommandLineProcessing(const CefString &processType, CefRefPtr<CefCommandLine> commandLine) override;
};
