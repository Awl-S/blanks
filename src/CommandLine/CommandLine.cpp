#include "../../include/CommandLine/CommandLine.h"
#include <string>
#include <vector>

/**
 * @brief Конструктор объекта CommandLine.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 *
 * Если количество аргументов меньше двух, тип команды будет определен как UNKNOWN.
 * В противном случае тип команды определяется на основе первого аргумента.
 * Остальные аргументы сохраняются в векторе args.
 */
CommandLine::CommandLine(int argc, char *argv[]) {
    if (argc < 2) {
        command_type = CommandType::UNKNOWN;
        return;
    }

    std::string command(argv[1]);
    if (command == "convert") {
        command_type = CommandType::CONVERT;
    }
    else if (command == "print") {
        command_type = CommandType::PRINT;
    }
    else if (command == "gen") {
        command_type = CommandType::GEN;
    }
    else {
        command_type = CommandType::UNKNOWN;
    }

    for (int i = 2; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }
}

/**
* @brief Получить тип команды.
*
* @return CommandType Тип команды.
*
* Возвращает тип команды, определенный при создании объекта CommandLine.
*/
CommandLine::CommandType CommandLine::get_command_type() const {
    return command_type;
}

/**
* @brief Получить аргументы команды.
*
* @return std::vector<std::string> Аргументы команды.
*
* Возвращает вектор строк, представляющих аргументы команды, сохраненные при создании объекта CommandLine.
*/
std::vector<std::string> CommandLine::get_args() const {
    return args;
}