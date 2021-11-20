#pragma once

#include <mutex>
#include <string>
#include <unordered_map>

#define ASSETS_FOLDER "assets/"
#define BINARY_EXTENSION ".bin"

struct Asset {
    std::vector<uint8_t> data;
    std::string mimeType;
};

class ArchiveManager {
public:
    class Repository {
        friend class ArchiveManager;
        friend std::pair<const std::string, Repository>;

    public:
        Repository(const Repository &) = delete;

        const Repository &operator=(const Repository &) = delete;

        Asset Read(const std::string &fileName);

    private:
        std::string package;

        Repository() = default;

        explicit Repository(const std::string &package);

        Repository &operator=(Repository &&other) = default;
    };

    ArchiveManager(const ArchiveManager &) = delete;
    const ArchiveManager &operator=(const ArchiveManager &) = delete;

    static Repository &GetRepository(const std::string &name) {
        static std::mutex mutex;
        static ArchiveManager manager;

        std::lock_guard<std::mutex> guard(mutex);

        if (manager.repositories.end() == manager.repositories.find(name))
            manager.repositories[name] = std::move(Repository(name));

        return manager.repositories[name];
    }

private:
    std::unordered_map<std::string, Repository> repositories;

    ArchiveManager() = default;
};
