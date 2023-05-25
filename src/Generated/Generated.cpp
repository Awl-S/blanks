#include "../../include/Generated/Generated.h"

/**
 * @brief Генерирует JSON-файл с заданным именем.
 * @param filename Имя файла для сохранения JSON.
 *
 * Функция генерирует JSON-файл, содержащий информацию о директориях,
 * тексте справки и имени файла PDF.
 */
void Generated::generateJsonFile(const std::string &filename) {
    nlohmann::json j;

    // Установка путей к различным директориям
    j["directories"]["tbl"] = "/path/to/tbl";
    j["directories"]["cfm"] = "/path/to/cfm";
    j["directories"]["zagotovki"] = "/path/to/zgt";
    j["directories"]["nabor"] = "/path/to/наборы";
    j["directories"]["font"] = "/path/to/font";

    // Установка текста справки
    j["help"] = "Текст помощи здесь...";

    // Установка имени файла PDF
    j["pdf_file_name"] = "example.pdf";

    // Открытие файла для записи
    std::ofstream o(filename);
    // Запись JSON-объекта в файл с отступом 4 пробела для форматирования
    o << std::setw(4) << j << std::endl;
}
