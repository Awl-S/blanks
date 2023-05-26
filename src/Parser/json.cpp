#include <fstream>
#include <iostream>
#include "../../include/Parser/json.h"

/**
 * @brief Конструктор класса json.
 * @param config_file_path Путь к файлу конфигурации.
 * @throws std::runtime_error Если не удалось открыть файл конфигурации.
 *
 * Конструктор открывает файл конфигурации и загружает его содержимое в объект config_json.
 * Если файл конфигурации не будет найден, выбрасывается исключение std::runtime_error.
 */
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

/**
* @brief Возвращает список файлов, соответствующих заданному ключу и поисковому запросу.
* @param key Ключ для получения пути к директории.
* @param search Поисковый запрос для фильтрации файлов.
* @return Список файлов, удовлетворяющих условиям поиска.
*
* Функция возвращает список файлов, найденных в директории, определенной ключом key.
* Файлы фильтруются с помощью поискового запроса search.
*/
std::filesystem::path json::getFilePath(const std::string &key) {
    if (!config_json.contains(key)) {
        throw std::runtime_error("Configuration file does not contain key: " + key);
    }
    return std::filesystem::u8path(config_json[key].get<std::string>());
}

/**
 * @brief Возвращает путь к файлу, соответствующий заданному ключу.
 * @param key Ключ для получения пути к файлу.
 * @return Путь к файлу, соответствующий заданному ключу.
 * @throws std::runtime_error Если ключ отсутствует в конфигурации.
 *
 * Функция возвращает путь к файлу, соответствующий заданному ключу key,
 * извлекая его из объекта config_json.
 * Если ключ отсутствует в конфигурации, выбрасывается исключение std::runtime_error.
 */
long long json::getInteger(const std::string &key) {
    if (!config_json.contains(key)) {
        throw std::runtime_error("Configuration file does not contain key: " + key);
    }
    return config_json[key];
}
/**
 * @brief Возвращает целочисленное значение, соответствующее заданному ключу.
 * @param key Ключ для получения целочисленного значения.
 * @return Целочисленное значение, соответствующее заданному ключу.
 * @throws std::runtime_error Если ключ отсутствует в конфигурации.
 *
 * Функция возвращает целочисленное значение, соответствующее заданному ключу key,
 * извлекая его из объекта config_json.
 * Если ключ отсутствует в конфигурации, выбрасывается исключение std::runtime_error.
 */
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










