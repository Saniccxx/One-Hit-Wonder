#pragma once
#include <string>
#include <filesystem>

namespace utils {
    inline std::string getRootFilePath(const std::string& filename) {
        std::filesystem::path current_dir = std::filesystem::current_path();
        std::filesystem::path parent_dir = current_dir.parent_path();


        if (std::filesystem::exists(current_dir / "cpps") && std::filesystem::is_directory(current_dir / "cpps")) {
            return (current_dir / filename).string();
        }


        if (std::filesystem::exists(parent_dir / "cpps") && std::filesystem::is_directory(parent_dir / "cpps")) {
            return (parent_dir / filename).string();
        }


        std::filesystem::path current_file = current_dir / filename;
        std::filesystem::path parent_file = parent_dir / filename;

        if (std::filesystem::exists(current_file)) {
            return current_file.string();
        }
        if (std::filesystem::exists(parent_file)) {
            return parent_file.string();
        }


        return current_file.string();
    }
}