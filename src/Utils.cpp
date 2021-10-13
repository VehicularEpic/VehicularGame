#include "Utils.hpp"

bool Utils::EndsWith(const std::string &string, const std::string &suffix) {
    if (string.length() >= suffix.length()) {
        const int i = string.compare(
                string.length() - suffix.length(), suffix.length(), suffix);

        return i == 0;
    }

    return false;
}
