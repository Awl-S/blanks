#include "../../include/Reader/FileReader.h"

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