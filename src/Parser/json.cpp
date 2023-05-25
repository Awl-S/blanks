#include <fstream>
#include <iostream>
#include "../../include/Parser/json.h"

std::vector<std::filesystem::path> json::getFileList(const std::string &key, const std::string &search) {
    std::vector<std::filesystem::path> files;
    std::filesystem::path directory = getFilePath(key);

    if (std::filesystem::exists(directory)) {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().filename().string().find(search) != std::string::npos) {
                files.push_back(entry.path());
                //std::cout << entry.path().string() << "\t" << entry.path() << std::endl;
            }
        }
    } else {
        // Обработка ошибки
        std::cout << "Directory does not exist or is not accessible: " << directory << std::endl;
    }

    return files;
}

std::filesystem::path json::getFilePath(const std::string &key) {
    if (!config_json.contains(key)) {
        throw std::runtime_error("Configuration file does not contain key: " + key);
    }
    return std::filesystem::u8path(config_json[key].get<std::string>());
}

long long json::getInteger(const std::string &key) {
    if (!config_json.contains(key)) {
        throw std::runtime_error("Configuration file does not contain key: " + key);
    }
    return config_json[key];
}

json::json(const std::string &config_file_path) {
    std::ifstream config_file(config_file_path);
    if (!config_file.is_open()) {
        throw std::runtime_error("Cannot open configuration file: " + config_file_path);
    }
    config_file >> config_json;
}

void json::display() {
    for (const auto& [key, value] : config_json.items()) {
        std::cout << key << ": " << value << std::endl;
    }
}