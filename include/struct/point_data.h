#ifndef BLANK_POINT_DATA_H
#define BLANK_POINT_DATA_H
#include "iostream"
#include <vector>
/**
 * @brief Структура для хранения координат точек.
 *
 * @param coordinates Вектор пар, представляющих координаты.
 */
struct point {
    std::vector<std::pair<double, double>> coordinates;
    /**
     * @brief Выводит координаты точек в стандартный вывод.
    */
    void display(){
        for (const auto& coord : coordinates) {
            std::cout << "(" << coord.first << "; " << coord.second << ")" << std::endl;
        }
    }
};
#endif //BLANK_POINT_DATA_H