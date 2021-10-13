#include "Utils.hpp"

ProcessType Utils::GetProcessType(const CefRefPtr<CefCommandLine> &commandLine) {
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

bool Utils::EndsWith(const std::string &string, const std::string &suffix) {
    if (string.length() >= suffix.length()) {
        const int i = string.compare(
                string.length() - suffix.length(), suffix.length(), suffix);

        return i == 0;
    }

    return false;
}
