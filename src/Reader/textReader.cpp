#include "../../include/Reader/textReader.h"
#include <iostream>
#include <regex>

/**
 * @brief Читает данные из файла в формате CFM
 *
 * @param data ссылка на структуру cfm, в которую будут записаны данные из файла
 * @throw std::runtime_error в случае ошибки открытия файла
 */
void textReader::read_cfm(cfm &data) {
    std::ifstream file(file_path_);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path_.string());
    }

    std::string line;
    size_t count = 1;
    while (std::getline(file, line)) {
        if (count == 1) {
            data.header = trim(line);
        } else if (count == 3) {
            data.blank = trim(line);
        } else if (count == 6) {
            std::istringstream iss(line);
            double temp;
            while (iss >> temp) {
                data.marks.push_back(temp);
            }
        } else if (count == 8) {
            std::istringstream(line) >> data.format[0] >> data.format[1];
        } else if (count == 10) {
            std::istringstream(line) >> data.diameter;
        } else if (count == 12) {
            std::istringstream(line) >> data.small_tick[0] >> data.small_tick[1];
        } else if (count == 14) {
            std::istringstream(line) >> data.big_tick[0] >> data.big_tick[1];
        } else if (count == 16) {
            std::istringstream(line) >> data.digital_tick[0] >> data.digital_tick[1] >> data.digital_tick[2] >> data.digital_tick[3];
        } else if (count == 18) {
            std::istringstream(line) >> data.digit_height >> data.label_height;
        } else if (count == 20) {
            data.tick_mask = trim(line);
        }
        count++;
    }
}

/**
 * @brief Читает данные из файла в формате ZGT
 *
 * @param data ссылка на структуру zgt, в которую будут записаны данные из файла
 * @throw std::runtime_error в случае ошибки открытия файла
 */
void textReader::read_zgt(zgt &data) {
    std::ifstream file(file_path_);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path_.string());
    }

    size_t count = 1;
    std::string line;
    while (std::getline(file, line)) {
        if (count == 2) {
            std::istringstream(line) >> data.diameter;
        } else if (count == 4) {
            std::istringstream(line) >> data.center_hole_diameter;
        } else if (count == 6) {
            std::istringstream iss(line);
            double temp;
            while (iss >> temp) {
                data.mounting_holes.push_back(temp);
            }
        } else if (count == 8) {
            std::istringstream iss(line);
            double temp;
            while (iss >> temp) {
                data.marker_position.push_back(temp);
            }
        } else if (count == 10) {
            std::istringstream(line) >> data.font_serial_number[0] >> data.font_serial_number[1];
        } else if (count == 12) {
            std::istringstream(line) >> data.stop_position[0] >> data.stop_position[1] >> data.stop_position[2];
        }
        count++;
    }
}

/**
 * @brief Читает данные из файла в формате TBL
 *
 * @param data ссылка на структуру tbl, в которую будут записаны данные из файла
 * @throw std::runtime_error в случае ошибки открытия файла или если не удается извлечь число из имени файла
 */
void textReader::read_tbl(tbl &data) {
    std::ifstream file(file_path_);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path_.string());
    }

    std::string file_name = file_path_.filename().string();

    std::string prefix = "scale";
    std::string suffix = ".tbl";

    auto start = file_name.find(prefix);
    auto end = file_name.find(suffix);

    if (start == std::string::npos || end == std::string::npos || start >= end) {
        throw std::runtime_error("Could not extract number from file name");
    }

    start += prefix.length();
    std::string number_str = file_name.substr(start, end - start);

    try {
        data.position = std::stoi(number_str);
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid number in file name: " + number_str);
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Number in file name is out of range: " + number_str);
    }

    std::string line;
    readLineString(file);
    data.model = readLineString(file);

    data.measurements.reserve(20);
    while (std::getline(file, line)) {
        double temp;
        double col2;
        double col3;
        if (std::istringstream(line) >> temp >> col2 >> col3) {
            data.measurements.push_back({col2, col3});
        }
    }
}

/**
 * @brief Читает данные из файла в формате точки
 *
 * @param data ссылка на структуру point, в которую будут записаны данные из файла
 * @throw std::runtime_error в случае ошибки открытия файла
 */
void textReader::read_point(point &data) {
    std::ifstream file(file_path_);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path_.string());
    }

    double x, y;
    while (file >> x >> y) {
        data.coordinates.emplace_back(x, y);
    }
}

/**
 * @brief Читает данные из файла в формате NBR
 *
 * @param data ссылка на структуру nbr, в которую будут записаны данные из файла
 * @throw std::runtime_error в случае ошибки открытия файла
 */
void textReader::read_nbr(nbr &data) {
    std::ifstream file(file_path_);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path_.string());
    }

    std::string line;
    size_t line_number = 1;
    while (std::getline(file, line)) {
        data.icon.insert(std::make_pair(line_number, line));
        line_number++;
    }
}
