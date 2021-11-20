#if defined(DEBUG_ENVIRONMENT)
#include "ArchiveManager.hpp"

#include "../Utils.hpp"

#include <cstdio>
#include <sstream>
#include <stdexcept>

#include <include/base/cef_build.h>

#if defined(OS_POSIX)
#include <cstring>
#define errno_ errno
#endif

static std::string GetMimeType(const std::string &fileName) {
#define MIME_TYPE(extension, mimeType)        \
    if (Utils::EndsWith(fileName, extension)) \
        return mimeType;

    /* Audio Files */
    MIME_TYPE(".wav", "audio/wav")
    MIME_TYPE(".ogg", "audio/ogg")
    MIME_TYPE(".mp3", "audio/mpeg")
    MIME_TYPE(".opus", "audio/opus")

    /* Text Files */
    MIME_TYPE(".css", "text/css")
    MIME_TYPE(".htm", "text/html")
    MIME_TYPE(".html", "text/html")

    /* Image Files */
    MIME_TYPE(".png", "image/png")
    MIME_TYPE(".jpg", "image/jpeg")
    MIME_TYPE(".jpeg", "image/jpeg")
    MIME_TYPE(".svg", "image/svg+xml")

    /* Font Files */
    MIME_TYPE(".otf", "font/otf")
    MIME_TYPE(".ttf", "font/ttf")
    MIME_TYPE(".woff", "font/woff")
    MIME_TYPE(".woff2", "font/woff2")

    /* Application Files */
    MIME_TYPE(".json", "application/json")
    MIME_TYPE(".js", "application/javascript")

    /* Default */
    return "text/plain";
}

ArchiveManager::Repository::Repository(const std::string &package)
    : package(ASSETS_FOLDER + package) {}

Asset ArchiveManager::Repository::Read(const std::string &fileName) {
    FILE *file;

    std::string filePath = this->package + "/" + fileName;
#if defined(OS_WIN)
    errno_t errno_ = fopen_s(&file, filePath.c_str(), "rb");
#elif defined(OS_POSIX)
    file = fopen(filePath.c_str(), "rb");
#endif

    if (nullptr == file) {
        std::stringstream stream;

#if defined(OS_WIN)
        char message[100];
        strerror_s(message, sizeof(message), errno_);
#elif defined(OS_POSIX)
        const char *message = strerror(errno_);
#endif

        stream << "Error loading " << filePath << ": " << message;

        throw std::runtime_error(stream.str().c_str());
    }

    fseek(file, 0, SEEK_END);

    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    std::vector<uint8_t> buffer(size);
    fread(&buffer[0], sizeof(uint8_t), size, file);

    fclose(file);

    Asset asset;

    asset.data = buffer;
    asset.mimeType = GetMimeType(fileName);

    return asset;
}
#endif
