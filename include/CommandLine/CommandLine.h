#ifndef BLANKS_COMMANDLINE_H
#define BLANKS_COMMANDLINE_H
#include <string>
#include <vector>

/**
 * @brief Класс для обработки командной строки.
 *
 * CommandLine - класс для обработки командной строки.
 * Он позволяет получить тип команды и список аргументов, переданных через командную строку.
 */
class CommandLine {
public:
    /**
     * @brief Конструктор класса CommandLine.
     *
     * Конструктор класса CommandLine принимает аргументы командной строки и инициализирует соответствующие поля класса.
     *
     * @param argc Количество аргументов командной строки.
     * @param argv Массив строк с аргументами командной строки.
     */
    CommandLine(int argc, char* argv[]);

    /**
     * @brief Перечисление CommandType для типа команды.
     */
    enum class CommandType {
        CONVERT, /**< Команда CONVERT. */
        PRINT, /**< Команда PRINT. */
        GEN,
        UNKNOWN /**< Неизвестная команда. */
    };

    /**
     * @brief Возвращает тип команды.
     *
     * Метод возвращает тип команды, указанный в командной строке.
     *
     * @return Тип команды.
     */
    [[nodiscard]] CommandType get_command_type() const;

    /**
     * @brief Возвращает список аргументов командной строки.
     *
     * Метод возвращает список аргументов командной строки, переданных после указания типа команды.
     *
     * @return Список аргументов командной строки.
     */
    [[nodiscard]] std::vector<std::string> get_args() const;

private:
    CommandType command_type; /**< Тип команды. */
    std::vector<std::string> args; /**< Список аргументов командной строки. */
};
#endif //BLANKS_COMMANDLINE_H