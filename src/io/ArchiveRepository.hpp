#pragma once

#include <string>
#include <vector>

#define ASSETS_FOLDER "assets/"
#define BINARY_EXTENSION ".bin"

typedef struct Asset {

    std::vector<uint8_t> data;

    std::string mimeType;

} Asset;

class ArchiveRepository {
public:
    explicit ArchiveRepository(const std::string &package);

    Asset Read(const std::string &fileName);

private:
    std::string package;
};
