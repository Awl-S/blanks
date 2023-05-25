#include "../../include/RenderPDF/RenderPDF.h"

/**
 * @brief Рисует индексы (цифры) на PDF странице.
 *
 * @param page Страница PDF, на которую будут нарисованы индексы.
 * @param blank Размер пустого пространства на странице.
 */
void RenderPDF::drawDigitIndices(HPDF_Page page, size_t blank) {
    // Установка размера шрифта для индексов
    setFontSize(page, cfm_data_.digit_height);

    // Цикл по всем меткам
    for (int i = 0; i < marks.size(); i++) {
        // Вычисление угла для каждой метки
        HPDF_REAL angle = 4.71239 - marks[i];

        // Форматирование текста метки
        auto text = formatText(i);

        // Вычисление ширины текста метки
        auto textWidth = HPDF_Page_TextWidth(page, text.c_str());

        // Вычисление координат x и y для текста метки
        HPDF_REAL x = calculateXCoordinate(angle, textWidth, blank);
        HPDF_REAL y = calculateYCoordinate(angle, blank);

        // Рисование текста метки на странице
        drawText(page, text, x, y);
    }
}

