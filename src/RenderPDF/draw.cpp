#include "../../include/RenderPDF/RenderPDF.h"
#include <cmath>

/**
 * @brief Устанавливает размер шрифта и размер страницы PDF.
 *
 * @param page Страница PDF, для которой нужно установить размер шрифта и размеры страницы.
 * @param size Размер шрифта для установки.
 */
void RenderPDF::setFontSize(HPDF_Page page, double size) {
    HPDF_Page_SetFontAndSize(page, font_, size);
    HPDF_Page_SetHeight(page, 420);
    HPDF_Page_SetWidth(page, 297);
}

/**
 * @brief Рисует круг на странице PDF.
 *
 * @param page Страница PDF, на которой будет нарисован круг.
 * @param x Координата X центра круга.
 * @param y Координата Y центра круга.
 * @param radius Радиус круга.
 */
void RenderPDF::drawCircle(HPDF_Page page, double x, double y, double radius) {
    HPDF_Page_Circle(page, x, y, radius);
    HPDF_Page_Stroke(page);
}

/**
 * @brief Рисует линию на странице PDF.
 *
 * @param page Страница PDF, на которой будет нарисована линия.
 * @param x1 Координата X начала линии.
 * @param y1 Координата Y начала линии.
 * @param x2 Координата X конца линии.
 * @param y2 Координата Y конца линии.
 */
void RenderPDF::draw_line(HPDF_Page page, HPDF_REAL x1, HPDF_REAL y1, HPDF_REAL x2, HPDF_REAL y2) {
    HPDF_Page_MoveTo(page, x1, y1);
    HPDF_Page_LineTo(page, x2, y2);
    HPDF_Page_Stroke(page);
}

/**
 * @brief Рисует текст на странице PDF.
 *
 * @param page Страница PDF, на которой будет нарисован текст.
 * @param text Текст для вывода на страницу.
 * @param x Координата X, где будет нарисован текст.
 * @param y Координата Y, где будет нарисован текст.
 */
void RenderPDF::drawText(HPDF_Page page, const std::string& text, HPDF_REAL x, HPDF_REAL y) {
    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, x, y);
    HPDF_Page_ShowText(page, text.c_str());
    HPDF_Page_EndText(page);
}

/**
 * @brief Форматирует текст с использованием заданной точности.
 *
 * @param i Индекс маркера, текст для которого нужно отформатировать.
 * @return Отформатированный текст.
 */
std::string RenderPDF::formatText(int i) {
    std::stringstream ss;
    ss.precision(cfm_data_.format[1]);
    ss << std::fixed << cfm_data_.marks[i];
    return ss.str();
}

/**
 * @brief Вычисляет координату X для текста маркера.
 *
 * @param angle Угол маркера.
 * @param textWidth Ширина текста маркера.
 * @param blank Размер пустого пространства на странице.
 * @return Координата X для текста маркера.
 */
HPDF_REAL RenderPDF::calculateXCoordinate(HPDF_REAL angle, double textWidth, size_t blank) {
    double marginText = 1;
    auto radius = (cfm_data_.diameter / 2.0) - cfm_data_.digital_tick[0] / 2;
    HPDF_REAL x = point_data_.coordinates[point_tbl[blank] - marginText].first +
                  (radius - cfm_data_.digital_tick[0]-1) * cos(angle) - textWidth / 2;
    return x;
}

/**
 * @brief Вычисляет координату Y для текста маркера.
 *
 * @param angle Угол маркера.
 * @param blank Размер пустого пространства на странице.
 * @return Координата Y для текста маркера.
 */
HPDF_REAL RenderPDF::calculateYCoordinate(HPDF_REAL angle, size_t blank) {
    double marginText = 1;
    auto radius = (cfm_data_.diameter / 2.0) - cfm_data_.digital_tick[0] / 2;
    HPDF_REAL y = point_data_.coordinates[point_tbl[blank] - marginText].second +
                  (radius - cfm_data_.digital_tick[0]-1) * sin(angle) - cfm_data_.digit_height / 2.5 + 0.5;
    return y;
}