#pragma once

#include <include/base/cef_build.h>
#include <include/cef_command_line.h>

enum ProcessType {
    PROCESS_TYPE_BROWSER,
    PROCESS_TYPE_RENDERER,
    PROCESS_TYPE_OTHER,
};

namespace Utils {

    ProcessType GetProcessType(const CefRefPtr<CefCommandLine> &commandLine);

}
