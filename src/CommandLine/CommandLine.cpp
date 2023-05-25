#include "../../include/CommandLine/CommandLine.h"
#include <string>
#include <vector>

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

CommandLine::CommandType CommandLine::get_command_type() const {
    return command_type;
}

std::vector<std::string> CommandLine::get_args() const {
    return args;
}