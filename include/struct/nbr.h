#ifndef BLANK_NBR_H
#define BLANK_NBR_H

#include <map>
#include <string>

/**
 * @struct nbr
 * @brief Структура для хранения данных типа nbr.
 *
 * Структура nbr содержит поле для хранения отображения иконок в виде ассоциативного контейнера std::map.
 * Ключом является размер иконки, а значением - строка, представляющая иконку.
 */
struct nbr{
    std::map<size_t, std::string> icon; /**< Контейнер для хранения иконок */

};
#endif //BLANK_NBR_H