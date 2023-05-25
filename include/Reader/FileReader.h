#ifndef BLANKS_FILEREADER_H
#define BLANKS_FILEREADER_H

#include <filesystem>
#include <utility>
#include "string"
#include "fstream"


class FileReader {
public:
    // Конструктор для инициализации файла
    explicit FileReader(std::filesystem::path file_path) : file_path_(std::move(file_path)) {}

protected:
    std::filesystem::path file_path_;
    static std::string readLineString(std::ifstream &file);
    static std::string trim(const std::string& s);
};
#endif //BLANKS_FILEREADER_H