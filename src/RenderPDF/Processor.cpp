#include "../../include/RenderPDF/RenderPDF.h"

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

void RenderPDF::sortTblData() {
    auto compare_position = [](const tbl& a, const tbl& b) {
        return a.position < b.position;
    };

    // Сортировка вектора tbl_data_ с использованием функции сравнения
    std::sort(tbl_data_.begin(), tbl_data_.end(), compare_position);
}

void RenderPDF::populatePointTbl() {
    for(auto i : tbl_data_){
        point_tbl.push_back(i.position);
    }
}