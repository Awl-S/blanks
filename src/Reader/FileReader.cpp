#include "../../include/Reader/FileReader.h"

/**
 * @brief Удаляет ведущие и завершающие пробелы из строки.
 * @param s Исходная строка.
 * @return Строка без ведущих и завершающих пробелов.
 *
 * Функция trim() удаляет ведущие и завершающие пробелы из строки s.
 * Также удаляются любые символы, которые являются пробельными или имеют значение кода больше 255.
 * Результат возвращается в виде новой строки.
 */
std::string FileReader::trim(const std::string &s) {
    auto start = s.begin();
    while (start != s.end() && (static_cast<unsigned char>(*start) > 255 || std::isspace(static_cast<unsigned char>(*start)))) {
        start++;
    }
    auto end = s.end();
    while (end != start && (static_cast<unsigned char>(*(end - 1)) > 255 || std::isspace(static_cast<unsigned char>(*(end - 1))))) {
        end--;
    }
    return std::string(start, end);
}

/**
 * @brief Читает строку из файла, удаляет ведущие и завершающие пробелы.
 * @param file Файловый поток для чтения строки.
 * @return Прочитанная строка без ведущих и завершающих пробелов.
 *
 * Функция readLineString() читает строку из указанного файлового потока file.
 * Затем удаляются ведущие и завершающие пробелы из строки.
 * Результат возвращается в виде новой строки.
 */
std::string FileReader::readLineString(std::ifstream &file) {
    std::string line;
    if (std::getline(file, line))
    {
        // Remove any leading/trailing whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
    }
    return line;
}