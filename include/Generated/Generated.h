#ifndef BLANKS_GENERATED_H
#define BLANKS_GENERATED_H

#include <fstream>
#include "nlohmann/json.hpp"

/**
 * @class Generated
 * @brief Класс, содержащий функцию для генерации JSON-файла.
 */
class Generated {
public:
    void generateJsonFile(const std::string& filename);
};

#endif //BLANKS_GENERATED_H