#ifndef BLANK_ZGT_H
#define BLANK_ZGT_H

#include <vector>
#include <array>
#include <iostream>

struct zgt{
    double diameter;
    double center_hole_diameter;
    std::vector<double> mounting_holes;
    std::vector<double> marker_position;
    std::array<double, 2> font_serial_number{}; // добавить
    std::array<double, 3> stop_position{}; // добавить

    void display() const {
        std::cout << "Diameter: " << diameter << "\n";
        std::cout << "Center Hole Diameter: " << center_hole_diameter << "\n";

        std::cout << "Mounting Holes: ";
        for (auto val : mounting_holes)
            std::cout << val << " ";
        std::cout << "\n";

        std::cout << "Marker Position: ";
        for (auto val : marker_position)
            std::cout << val << " ";
        std::cout << "\n";

        std::cout << "Font Serial Number: " << font_serial_number[0] << " " << font_serial_number[1] << "\n";

        std::cout << "Stop Position: " << stop_position[0] << " " << stop_position[1] << " " << stop_position[2] << "\n";
    }
};
#endif //BLANK_ZGT_H