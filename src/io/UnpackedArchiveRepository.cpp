#if defined(DEBUG_ENVIRONMENT)
#include "ArchiveRepository.hpp"

#include "../Utils.hpp"

#include <cstdio>
#include <sstream>
#include <stdexcept>

static std::string GetMimeType(const std::string &fileName) {
#define MIME_TYPE(extension, mimeType)        \
    if (Utils::EndsWith(fileName, extension)) \
        return mimeType;

    /* Audio Files */
    MIME_TYPE(".wav", "audio/wav");
    MIME_TYPE(".ogg", "audio/ogg");
    MIME_TYPE(".mp3", "audio/mpeg");
    MIME_TYPE(".opus", "audio/opus");

    /* Text Files */
    MIME_TYPE(".css", "text/css");
    MIME_TYPE(".htm", "text/html");
    MIME_TYPE(".html", "text/html");

    /* Image Files */
    MIME_TYPE(".png", "image/png");
    MIME_TYPE(".jpg", "image/jpeg");
    MIME_TYPE(".jpeg", "image/jpeg");
    MIME_TYPE(".svg", "image/svg+xml");

    /* Font Files */
    MIME_TYPE(".otf", "font/otf");
    MIME_TYPE(".ttf", "font/ttf");
    MIME_TYPE(".woff", "font/woff");
    MIME_TYPE(".woff2", "font/woff2");

    /* Application Files */
    MIME_TYPE(".json", "application/json");
    MIME_TYPE(".js", "application/javascript");

    /* Default */
    return "text/plain";
}

ArchiveRepository::ArchiveRepository(const std::string &package)
    : package(ASSETS_FOLDER + package) {}

Asset ArchiveRepository::Read(const std::string &fileName) {
    FILE *file;

    std::string filePath = this->package + "/" + fileName;
    errno_t error = fopen_s(&file, filePath.c_str(), "rb");

    if (error > 0) {
        std::stringstream stream;

        if (error == ENOENT) {
            stream << "File '" << filePath << "' not found";
        } else {
            stream << "Error loading '" << filePath << "' (CODE " << error << ")";
        }

        throw std::runtime_error(stream.str().c_str());
    }

    fseek(file, 0, SEEK_END);

    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    std::vector<uint8_t> buffer(size);
    fread_s(&buffer[0], sizeof(uint8_t) * size, sizeof(uint8_t), size, file);

    fclose(file);

    Asset asset;

    asset.data = buffer;
    asset.mimeType = GetMimeType(fileName);

    return asset;
}
#endif
