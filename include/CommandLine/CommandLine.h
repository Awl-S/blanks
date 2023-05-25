#ifndef BLANKS_COMMANDLINE_H
#define BLANKS_COMMANDLINE_H
#include <string>
#include <vector>
/**
 * @class CommandLine
 * @brief Класс, представляющий интерфейс командной строки.
 *
 * Этот класс обрабатывает аргументы командной строки и категоризирует тип команды
 * на основе аргументов. В настоящее время поддерживаются команды 'convert', 'print' и 'gen'.
 */
class CommandLine {
public:
    CommandLine(int argc, char* argv[]);
    enum class CommandType {
        CONVERT,
        PRINT,
        GEN,
        UNKNOWN
    };
    [[nodiscard]] CommandType get_command_type() const;
    [[nodiscard]] std::vector<std::string> get_args() const;
private:
    CommandType command_type;
    std::vector<std::string> args;
};
#endif