#ifndef BLANK_POINT_DATA_H
#define BLANK_POINT_DATA_H

#include <vector>

struct point {
    std::vector<std::pair<double, double>> coordinates;
    void display(){
        for (const auto& coord : coordinates) {
            std::cout << "(" << coord.first << "; " << coord.second << ")" << std::endl;
        }
    }
};
#endif //BLANK_POINT_DATA_H