#if defined(DEBUG_ENVIRONMENT)
#include "ArchiveRepository.hpp"

ArchiveRepository::ArchiveRepository(const std::string &package)
    : package(ASSETS_FOLDER + package) {}

std::vector<uint8_t> ArchiveRepository::read(const std::string &name) {
    FILE *file;

    std::string filePath = this->package + "/" + name;
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
    return buffer;
}
#endif
