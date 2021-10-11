#pragma once

#include "GameWindow.hpp"
#include "gui/WebViewClient.hpp"
#include "gui/WebViewEventHandler.hpp"

#include <include/base/cef_build.h>

enum ProcessType {
    PROCESS_TYPE_BROWSER,
    PROCESS_TYPE_RENDERER,
    PROCESS_TYPE_OTHER,
};

namespace Game {

    int Run(const CefMainArgs &args, void *sandbox);

}
