#ifndef BLANKS_TEXTREADER_H
#define BLANKS_TEXTREADER_H

#include <regex>
#include "FileReader.h"
#include "../struct/nbr.h"
#include "../struct/point_data.h"
#include "../struct/tbl.h"
#include "../struct/cfm.h"
#include "../struct/zgt.h"

/**
 * @class textReader
 * @brief Класс для чтения текстового файла.
 *
 * Класс textReader наследуется от класса FileReader и предоставляет функциональность чтения различных типов данных из текстового файла.
 */
class textReader : public FileReader {
public:
    /**
     * @brief Конструктор класса textReader.
     * @param file_path Путь к файлу для чтения.
     *
     * Конструктор инициализирует объект textReader с указанным путем к файлу file_path
     * и вызывает конструктор базового класса FileReader.
     */
    explicit textReader(const std::filesystem::path& file_path) : FileReader(file_path) {}

    /**
     * @brief Читает данные типа nbr из файла.
     * @param data Ссылка на объект типа nbr для сохранения прочитанных данных.
     *
     * Функция read_nbr() читает данные типа nbr из файла и сохраняет их в объекте data.
     */
    void read_nbr(nbr& data);

    /**
     * @brief Читает данные типа point из файла.
     * @param data Ссылка на объект типа point для сохранения прочитанных данных.
     *
     * Функция read_point() читает данные типа point из файла и сохраняет их в объекте data.
     */
    void read_point(point& data);

    /**
     * @brief Читает данные типа tbl из файла.
     * @param data Ссылка на объект типа tbl для сохранения прочитанных данных.
     *
     * Функция read_tbl() читает данные типа tbl из файла и сохраняет их в объекте data.
     */
    void read_tbl(tbl& data);

    /**
     * @brief Читает данные типа cfm из файла.
     * @param data Ссылка на объект типа cfm для сохранения прочитанных данных.
     *
     * Функция read_cfm() читает данные типа cfm из файла и сохраняет их в объекте data.
     */
    void read_cfm(cfm& data);

    /**
     * @brief Читает данные типа zgt из файла.
     * @param data Ссылка на объект типа zgt для сохранения прочитанных данных.
     *
     * Функция read_zgt() читает данные типа zgt из файла и сохраняет их в объекте data.
     */
    void read_zgt(zgt& data);
};

#endif //BLANKS_TEXTREADER_H