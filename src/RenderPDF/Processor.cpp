#include "../../include/RenderPDF/RenderPDF.h"

/**
 * @brief Проверяет наличие дубликатов координат в point_data_.
 *
 * @return Возвращает true, если есть дубликаты координат, указывающие на необходимость новой страницы, иначе false.
 */
bool RenderPDF::checkForNewPage() {
    for (size_t i = 0; i < point_data_.coordinates.size(); ++i) {
        for (size_t j = i + 1; j < point_data_.coordinates.size(); ++j) {
            if (point_data_.coordinates[i] == point_data_.coordinates[j]) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Сортирует данные в tbl_data_ по положению элементов.
 *
 * Эта функция использует стандартную функцию сортировки из библиотеки алгоритмов STL и
 * лямбда-функцию для сравнения положения элементов.
 */
void RenderPDF::sortTblData() {
    auto compare_position = [](const tbl& a, const tbl& b) {
        return a.position < b.position;
    };

    // Сортировка вектора tbl_data_ с использованием функции сравнения
    std::sort(tbl_data_.begin(), tbl_data_.end(), compare_position);
}

/**
 * @brief Заполняет point_tbl данными из tbl_data_.
 *
 * Эта функция используется для копирования данных о позициях из tbl_data_ в point_tbl.
 */
void RenderPDF::populatePointTbl() {
    for(auto i : tbl_data_){
        point_tbl.push_back(i.position);
    }
}