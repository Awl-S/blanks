#ifndef BLANKS_RENDERPDF_H
#define BLANKS_RENDERPDF_H

#include <vector>
#include <hpdf.h>
#include <filesystem>
#include <cmath>
#include "../struct/cfm.h"
#include "../struct/zgt.h"
#include "../struct/nbr.h"
#include "../struct/point_data.h"
#include "../struct/tbl.h"

/**
 * @class RenderPDF
 * @brief Класс для генерации PDF-файла.
 *
 * Класс RenderPDF предоставляет функциональность для создания и рендеринга PDF-файлов.
 */
class RenderPDF {

    HPDF_Font loadFont(const std::string& fontPath);
    void sortTblData();
    void populatePointTbl();
    bool checkForNewPage();

    void createA3Page();

    void setFontSize(HPDF_Page page, double size);

    static void drawCircle(HPDF_Page page, double x, double y, double radius);

    static void draw_line(HPDF_Page page, HPDF_REAL x1, HPDF_REAL y1, HPDF_REAL x2, HPDF_REAL y2);

    void generate_Marks(size_t blank);

    void drawDigitIndices(HPDF_Page page, size_t blank);

    void drawMainLines(HPDF_Page page, size_t blank);

    void drawAdditionalTicks(HPDF_Page page, size_t blank);

    void initializeData(cfm cfm_data, zgt zgt_data, const std::vector<tbl> &tbl_data, nbr nbr_data, point point_data, std::filesystem::path fontPath);
    void initializePDF();
    void adjustFontSize();

    HPDF_REAL calculateYCoordinate(HPDF_REAL angle, size_t blank);
    HPDF_REAL calculateXCoordinate(HPDF_REAL angle, double textWidth, size_t blank);
    std::string formatText(int i);
    void drawText(HPDF_Page page, const std::string& text, HPDF_REAL x, HPDF_REAL y);

public:
    void generatePDF(std::string& filename, std::vector<std::string> args);

    RenderPDF(cfm cfm_data, zgt zgt_data, const std::vector<tbl> &tbl_data, nbr nbr_data, point point_data, std::filesystem::path fontPath);

    ~RenderPDF();

private:
    const double PI = 3.14159265358979323846; /**< Значение числа Пи */
    double margitText = 1; /**< Отступ для текста */
    bool new_page = false; /**< Флаг новой страницы */
    std::filesystem::path fontPath_; /**< Путь к файлу шрифта */

    HPDF_Doc pdf_; /**< Документ PDF */
    HPDF_Font font_; /**< Шрифт PDF */

    cfm cfm_data_; /**< Данные типа cfm */
    zgt zgt_data_; /**< Данные типа zgt */
    nbr nbr_data_; /**< Данные типа nbr */
    point point_data_; /**< Данные типа point */
    std::vector<tbl> tbl_data_; /**< Вектор данных типа tbl */
    std::vector<size_t> point_tbl; /**< Таблица точек */
    std::vector<double> marks; /**< Метки */
};
#endif //BLANKS_RENDERPDF_H