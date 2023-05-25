#ifndef BLANK_ZGT_H
#define BLANK_ZGT_H

#include <vector>
#include <array>
#include <iostream>

/**
 * @struct zgt
 * @brief Структура для хранения данных типа zgt.
 *
 * Структура zgt содержит поля для хранения различных данных типа zgt,
 * которые представляют параметры для зубчатой передачи.
 */
struct zgt{
    double diameter; /**< Диаметр */
    double center_hole_diameter; /**< Диаметр центрального отверстия */
    std::vector<double> mounting_holes; /**< Отверстия для крепления */
    std::vector<double> marker_position; /**< Позиция маркера */
    std::array<double, 2> font_serial_number{}; /**< Серийный номер шрифта */
    std::array<double, 3> stop_position{}; /**< Позиция стопора */

    /**
     * @brief Выводит содержимое структуры zgt на консоль.
     *
     * Функция display() выводит значения каждого поля структуры zgt на консоль.
     * Затем выводит значения отверстий для крепления, позицию маркера,
     * серийный номер шрифта и позицию стопора.
     */
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