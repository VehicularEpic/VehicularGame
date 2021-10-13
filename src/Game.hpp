#pragma once

#include <include/base/cef_build.h>
#include <include/cef_base.h>

enum ProcessType {
    PROCESS_TYPE_BROWSER,
    PROCESS_TYPE_RENDERER,
    PROCESS_TYPE_OTHER,
};

namespace Game {

    int Run(const CefMainArgs &args, void *sandbox);

}
