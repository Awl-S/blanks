#include "../../include/RenderPDF/RenderPDF.h"
#include <ios>
#include <sstream>
#include <cmath>

HPDF_REAL RenderPDF::calculateXCoordinate(HPDF_REAL angle, double textWidth, size_t blank) {
    double marginText = 1;
    auto radius = (cfm_data_.diameter / 2.0) - cfm_data_.digital_tick[0] / 2;
    HPDF_REAL x = point_data_.coordinates[point_tbl[blank] - marginText].first +
                  (radius - cfm_data_.digital_tick[0]-1) * cos(angle) - textWidth / 2;
    return x;
}

HPDF_REAL RenderPDF::calculateYCoordinate(HPDF_REAL angle, size_t blank) {
    double marginText = 1;
    auto radius = (cfm_data_.diameter / 2.0) - cfm_data_.digital_tick[0] / 2;
    HPDF_REAL y = point_data_.coordinates[point_tbl[blank] - marginText].second +
                  (radius - cfm_data_.digital_tick[0]-1) * sin(angle) - cfm_data_.digit_height / 2.5 + 0.5;
    return y;
}

std::string RenderPDF::formatText(int i) {
    std::stringstream ss;
    ss.precision(cfm_data_.format[1]);
    ss << std::fixed << cfm_data_.marks[i];
    return ss.str();
}

void RenderPDF::drawText(HPDF_Page page, const std::string& text, HPDF_REAL x, HPDF_REAL y) {
    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, x, y);
    HPDF_Page_ShowText(page, text.c_str());
    HPDF_Page_EndText(page);
}

void RenderPDF::drawDigitIndices(HPDF_Page page, size_t blank) {
    setFontSize(page, cfm_data_.digit_height);
    for (int i = 0; i < marks.size(); i++) {
        HPDF_REAL angle = 4.71239 - marks[i];
        auto text = formatText(i);
        auto textWidth = HPDF_Page_TextWidth(page, text.c_str());
        HPDF_REAL x = calculateXCoordinate(angle, textWidth, blank);
        HPDF_REAL y = calculateYCoordinate(angle, blank);
        drawText(page, text, x, y);
    }
}


/*
void RenderPDF::drawDigitIndices(HPDF_Page page, size_t blank) {
    auto radius = (cfm_data_.diameter / 2.0) - cfm_data_.digital_tick[0] / 2;
    setFontSize(page, cfm_data_.digit_height);
    for (int i = 0; i < marks.size(); i++) {
        HPDF_REAL angle = 4.71239 - marks[i];

        std::stringstream ss;
        ss.precision(cfm_data_.format[1]);
        ss << std::fixed << cfm_data_.marks[i];
        double margitText = 1;
        auto textWidth = HPDF_Page_TextWidth(page, ss.str().c_str());

        HPDF_REAL x = point_data_.coordinates[point_tbl[blank] - margitText].first +
                      (radius - cfm_data_.digital_tick[0]-1) * cos(angle) - textWidth / 2;
        // поделено на 2 для небольшой коррекции горизонтального выравнивания
        HPDF_REAL y = point_data_.coordinates[point_tbl[blank] - margitText].second +
                      (radius - cfm_data_.digital_tick[0]-1) * sin(angle) - cfm_data_.digit_height/2.5 + 0.5;
        // поделено на 2.5 для небольшой коррекции вертикального выравнивания
        // добавлено 0.5 для коррекции горизонтального выравнивания
        HPDF_Page_BeginText(page);
        HPDF_Page_MoveTextPos(page, x, y);
        HPDF_Page_ShowText(page, ss.str().c_str());
        HPDF_Page_EndText(page);
    }
}
 */
