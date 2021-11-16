#include "Game.hpp"
#include "GameWindow.hpp"
#include "GameWindowEventHandler.hpp"

#include "cef/RenderProcess.hpp"
#include "gui/WebViewApp.hpp"

void Game::Run(const CefMainArgs &args, void *sandbox) {
    GameWindow display("No Name Game", 800, 600, true);
    GLFWwindow *window = display.GetWindow();
    GameWindowEventHandler handler(window);

    CefRefPtr<WebViewRenderer> webview = new WebViewRenderer(display.GetWidth(), display.GetHeight());
    CefRefPtr<WebViewClient> client = new WebViewClient(webview);
    CefRefPtr<WebViewApp> app = new WebViewApp(client);

    CefExecuteProcess(args, app, sandbox);

    CefSettings settings;
    settings.log_severity = LOGSEVERITY_DISABLE;

    CefInitialize(args, settings, app, sandbox);

    CefWindowInfo windowInfo;
    CefBrowserSettings browserSettings;

#if defined(OS_WIN)
    windowInfo.SetAsWindowless(glfwGetWin32Window(window));
#endif

#if defined(OS_LINUX)
    windowInfo.SetAsWindowless(glfwGetX11Window(window));
#endif

    browserSettings.windowless_frame_rate = 60;

    const char *testUrl = "webview://client/index.html";

    CefRefPtr<CefBrowser> browser = CefBrowserHost::CreateBrowserSync(
            windowInfo, client, testUrl, browserSettings, nullptr, nullptr);

    handler.AddFramebufferSizeListener([webview, browser](int width, int height) {
        glViewport(0, 0, width, height);
        webview->SetSize(width, height);
        browser->GetHost()->WasResized();
    });

    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)) {
        webview->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        CefDoMessageLoopWork();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

int Game::Main(const CefMainArgs &args, void *sandbox, ProcessType type) {
    if (PROCESS_TYPE_BROWSER == type) {
        Game::Run(args, sandbox);
        CefShutdown();

        return (EXIT_SUCCESS);
    }

    if (PROCESS_TYPE_RENDERER == type) {
        return CefExecuteProcess(args, new RenderProcess(), sandbox);
    }

    return CefExecuteProcess(args, new BasicApp(), sandbox);
}

static ProcessType GetProcessType(const CefRefPtr<CefCommandLine> &commandLine) {
    if (!commandLine->HasSwitch("type"))
        return PROCESS_TYPE_BROWSER;

    const std::string &type = commandLine->GetSwitchValue("type");

    if (type == "renderer")
        return PROCESS_TYPE_RENDERER;

#if defined(OS_LINUX)
    if (type == "zygote")
        return PROCESS_TYPE_RENDERER;
#endif

    return PROCESS_TYPE_OTHER;
}

#if defined(OS_WIN)
#include <include/cef_sandbox_win.h>

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPWSTR lpCmdLine, int nShowCmd) {
    CefEnableHighDPISupport();
    CefMainArgs args(hInstance);

    CefRefPtr<CefCommandLine> commandLine = CefCommandLine::CreateCommandLine();
    commandLine->InitFromString(::GetCommandLineW());

    CefScopedSandboxInfo scopedSandbox;
    return Game::Main(args, scopedSandbox.sandbox_info(), GetProcessType(commandLine));
}
#else
int main(int argc, char *argv[]) {
    CefMainArgs args(argc, argv);

    CefRefPtr<CefCommandLine> commandLine = CefCommandLine::CreateCommandLine();
    commandLine->InitFromArgv(argc, argv);

    return Game::Main(args, nullptr, GetProcessType(commandLine));
}
#endif
