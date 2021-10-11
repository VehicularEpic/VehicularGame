#if defined(RELEASE_ENVIRONMENT)
#include "ArchiveRepository.hpp"

ArchiveRepository::ArchiveRepository(const std::string &package)
    : package(ASSETS_FOLDER + package + BINARY_EXTENSION) {
    // TODO: Packaged binary archive reader
}
#endif
