#ifndef BLANKS_GENERATED_H
#define BLANKS_GENERATED_H

#include <fstream>
#include "nlohmann/json.hpp"

class Generated {
public:
    void generateJsonFile(const std::string& filename) {
        nlohmann::json j;

        j["directories"]["tbl"] = "/path/to/tbl";
        j["directories"]["cfm"] = "/path/to/cfm";
        j["directories"]["zagotovki"] = "/path/to/zgt";
        j["directories"]["nabor"] = "/path/to/наборы";
        j["directories"]["font"] = "/path/to/font";
        j["help"] = "Текст помощи здесь...";
        j["pdf_file_name"] = "example.pdf";

        std::ofstream o(filename);
        o << std::setw(4) << j << std::endl;
    }
};
#endif //BLANKS_GENERATED_H