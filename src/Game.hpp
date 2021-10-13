#pragma once

#include "GameWindow.hpp"
#include "gui/WebViewClient.hpp"

#include <include/base/cef_build.h>

namespace Game {

    int Run(const CefMainArgs &args, void *sandbox);

}
