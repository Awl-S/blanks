#ifndef BLANKS_FILEREADER_H
#define BLANKS_FILEREADER_H

#include <filesystem>
#include <utility>
#include "string"
#include "fstream"

/**
 * @class FileReader
 * @brief Класс для чтения файла.
 *
 * Класс FileReader предоставляет функциональность для чтения файлов и обработки строк.
 */
class FileReader {
public:
    /**
     * @brief Конструктор класса FileReader.
     * @param file_path Путь к файлу для чтения.
     *
     * Конструктор инициализирует объект FileReader с указанным путем к файлу file_path.
     */
    explicit FileReader(std::filesystem::path file_path) : file_path_(std::move(file_path)) {}

protected:
    std::filesystem::path file_path_; /**< Путь к файлу */

    /**
     * @brief Читает строку из файла и удаляет ведущие и завершающие пробелы.
     * @param file Файловый поток для чтения строки.
     * @return Прочитанная строка без ведущих и завершающих пробелов.
     *
     * Функция readLineString() читает строку из указанного файлового потока file.
     * Затем удаляются ведущие и завершающие пробелы из строки.
     * Результат возвращается в виде новой строки.
     */
    static std::string readLineString(std::ifstream &file);

    /**
     * @brief Удаляет ведущие и завершающие пробелы из строки.
     * @param s Исходная строка.
     * @return Строка без ведущих и завершающих пробелов.
     *
     * Функция trim() удаляет ведущие и завершающие пробелы из строки s.
     * Результат возвращается в виде новой строки.
     */
    static std::string trim(const std::string& s);
};

#endif //BLANKS_FILEREADER_H