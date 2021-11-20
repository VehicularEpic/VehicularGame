#include "BasicApp.hpp"

void BasicApp::OnBeforeCommandLineProcessing(const CefString &processType, CefRefPtr<CefCommandLine> commandLine) {
    if (processType.empty() /* Browser process */) {
#if defined(DEBUG_ENVIRONMENT)
        commandLine->AppendSwitchWithValue("remote-debugging-port", "9222");
#endif
        commandLine->AppendSwitchWithValue("autoplay-policy", "no-user-gesture-required");
    }
}

void BasicApp::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) {
    registrar->AddCustomScheme("webview", CEF_SCHEME_OPTION_STANDARD);
}