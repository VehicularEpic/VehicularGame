#pragma once

#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#define ASSETS_FOLDER "assets/"
#define BINARY_EXTENSION ".bin"

class ArchiveRepository {
public:
    explicit ArchiveRepository(const std::string &package);

    std::vector<uint8_t> read(const std::string &name);

private:
    std::string package;
};
