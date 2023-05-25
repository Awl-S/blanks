#ifndef BLANK_TBL_H
#define BLANK_TBL_H

#include <string>
#include <vector>
#include <iostream>

struct tbl {
    int position;
    std::string model;
    std::vector<std::vector<double>> measurements;

    void display() const {
        std::cout << "Position: " << position << "\n";
        std::cout << "Model: " << model << "\n";

        std::cout << "Measurements:\n";
        for (const auto& row : measurements) {
            for (const auto& value : row) {
                std::cout << value << " ";
            }
            std::cout << "\n";
        }
    }
};
#endif //BLANK_TBL_H