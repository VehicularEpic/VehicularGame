#include "Game.hpp"
#include "Utils.hpp"

int Game::Run(const CefMainArgs &args, void *sandbox) {
    GameWindow display("No Name Game", 800, 600, true);
    GLFWwindow *window = display.GetWindow();

    CefRefPtr<WebViewRenderer> webview = new WebViewRenderer(display.GetWidth(), display.GetHeight());
    CefRefPtr<WebViewClient> client = new WebViewClient(webview);

    CefExecuteProcess(args, client, sandbox);

    CefSettings settings;
    settings.log_severity = LOGSEVERITY_DISABLE;

    CefInitialize(args, settings, client, sandbox);

    CefWindowInfo windowInfo;
    CefBrowserSettings browserSettings;

#if defined(OS_WIN)
    windowInfo.SetAsWindowless(glfwGetWin32Window(window));
#endif

#if defined(OS_LINUX)
    windowInfo.SetAsWindowless(glfwGetX11Window(window));
#endif

    browserSettings.windowless_frame_rate = 60;

    const char *testUrl = "https://www.youtube.com/embed/iik25wqIuFo?autoplay=1&controls=0";

    CefRefPtr<CefBrowser> browser = CefBrowserHost::CreateBrowserSync(
            windowInfo, client, testUrl, browserSettings, nullptr, nullptr);

    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)) {
        webview->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        CefDoMessageLoopWork();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    // TODO: remove the following CefBrowser unref workaround
    browser = nullptr;

    CefShutdown();

    return (EXIT_SUCCESS);
}

#if defined(OS_WIN)
#include <include/cef_sandbox_win.h>

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPWSTR lpCmdLine, int nShowCmd) {
    CefScopedSandboxInfo scopedSandbox;

    CefEnableHighDPISupport();
    CefMainArgs args(hInstance);

    CefRefPtr<CefCommandLine> commandLine = CefCommandLine::CreateCommandLine();
    commandLine->InitFromString(::GetCommandLineW());

    if (PROCESS_TYPE_BROWSER == Utils::GetProcessType(commandLine)) {
        return Game::Run(args, scopedSandbox.sandbox_info());
    }

    return CefExecuteProcess(args, nullptr, scopedSandbox.sandbox_info());
}
#else
int main(int argc, char *argv[]) {
    CefMainArgs args(argc, argv);

    CefRefPtr<CefCommandLine> commandLine = CefCommandLine::CreateCommandLine();
    commandLine->InitFromArgv(argc, argv);

    if (PROCESS_TYPE_BROWSER == GetProcessType(commandLine)) {
        return Game::Run(args, nullptr);
    }

    return CefExecuteProcess(args, nullptr, nullptr);
}
#endif
