#ifndef BLANK_CFM_H
#define BLANK_CFM_H

#include <string>
#include <vector>
#include <array>
#include <iostream>

/**
 * @struct cfm
 * @brief Структура для хранения данных типа cfm.
 *
 * Структура cfm содержит поля для хранения различных данных типа cfm,
 * которые представляют параметры для отображения графика.
 */
struct cfm {
    std::string header; /**< Заголовок */
    std::string blank; /**< модель */
    std::vector<double> marks; /**< Метки */
    std::array<int, 2> format; /**< Формат */
    int diameter; /**< Диаметр */
    std::array<double, 2> small_tick; /**< Малый делитель */
    std::array<double, 2> big_tick; /**< Большой делитель */
    std::array<double, 4> digital_tick; /**< Цифровой делитель */
    int digit_height; /**< Высота цифр */
    int label_height; /**< Высота меток */
    std::string tick_mask; /**< Маска делителей */


    /**
     * @brief Выводит содержимое структуры cfm на консоль.
     *
     * Функция display() выводит значения каждого поля структуры cfm на консоль.
     */
    void display() const {
        std::cout << "Header: " << header << "\n";
        std::cout << "Blank: " << blank << "\n";

        std::cout << "Marks: ";
        for (auto val : marks)
            std::cout << val << " ";
        std::cout << "\n";

        std::cout << "Format: " << format[0] << " " << format[1] << "\n";

        std::cout << "Diameter: " << diameter << "\n";

        std::cout << "Small Tick: " << small_tick[0] << " " << small_tick[1] << "\n";

        std::cout << "Big Tick: " << big_tick[0] << " " << big_tick[1] << "\n";

        std::cout << "Digital Tick: " << digital_tick[0] << " " << digital_tick[1] << " " << digital_tick[2] << " " << digital_tick[3] << "\n";

        std::cout << "Digit Height: " << digit_height << "\n";

        std::cout << "Label Height: " << label_height << "\n";

        std::cout << "Tick Mask: " << tick_mask << "\n";
    }
};
#endif //BLANK_CFM_H