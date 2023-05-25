#include <stdexcept>
#include "../../include/RenderPDF/RenderPDF.h"

/**
 * @brief Создает новую страницу формата A3.
 */
 void RenderPDF::createA3Page() {
    HPDF_Page page = HPDF_AddPage(pdf_);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A3, HPDF_PAGE_PORTRAIT);
}

/**
 * @brief Загружает шрифт из указанного файла.
 *
 * @param fontPath Путь к файлу шрифта.
 * @return Возвращает объект HPDF_Font.
 * @throw std::runtime_error если не удается загрузить шрифт.
 */
HPDF_Font RenderPDF::loadFont(const std::string& fontPath) {
    auto font_name = HPDF_LoadTTFontFromFile(pdf_, fontPath.c_str(), HPDF_TRUE);
    auto font = HPDF_GetFont(pdf_, font_name, "CP1251");

    if(!font){
        throw std::runtime_error("Не удалось загрузить шрифт.");
    }

    return font;
}

/**
 * @brief Деструктор класса RenderPDF.
 *
 * Освобождает ресурсы, связанные с объектом HPDF_Doc.
 */
RenderPDF::~RenderPDF() {
    if (pdf_) {
        HPDF_Free(pdf_);
    }
}

/**
 * @brief Конструктор класса RenderPDF.
 *
 * Инициализирует данные, создает объект PDF, подгоняет размер шрифта, загружает шрифт,
 * сортирует данные таблицы и заполняет таблицу точек.
 */
RenderPDF::RenderPDF(cfm cfm_data, zgt zgt_data, const std::vector<tbl> &tbl_data, nbr nbr_data, point point_data, std::filesystem::path fontPath) {
    initializeData(std::move(cfm_data), std::move(zgt_data), tbl_data, std::move(nbr_data), std::move(point_data), fontPath);
    initializePDF();
    adjustFontSize();
    font_ = loadFont(fontPath_.string());
    sortTblData();
    populatePointTbl();
    new_page = checkForNewPage();
}

/**
 * @brief Инициализирует данные.
 *
 * @param cfm_data Данные для cfm.
 * @param zgt_data Данные для zgt.
 * @param tbl_data Данные для tbl.
 * @param nbr_data Данные для nbr.
 * @param point_data Данные для точки.
 * @param fontPath Путь к файлу шрифта.
 */
 void RenderPDF::initializeData(cfm cfm_data, zgt zgt_data, const std::vector<tbl> &tbl_data, nbr nbr_data, point point_data, std::filesystem::path fontPath) {
    cfm_data_ = std::move(cfm_data);
    zgt_data_ = std::move(zgt_data);
    tbl_data_ = tbl_data;
    nbr_data_ = std::move(nbr_data);
    point_data_ = std::move(point_data);
    fontPath_ = fontPath;
}

/**
 * @brief Инициализирует объект HPDF_Doc для работы с PDF.
 *
 * @throw std::runtime_error если не удается создать объект PDF.
 */void RenderPDF::initializePDF() {
    pdf_ = HPDF_New(nullptr, nullptr);
    if(!pdf_){
        throw std::runtime_error("Не удалось создать PDF документ.");
    }
}

/**
 * @brief Подгоняет размер шрифта.
 *
 * Использует коэффициент поправки размера для шрифта GOST_B.
 */
 void RenderPDF::adjustFontSize() {
    cfm_data_.digit_height*=1.090248; //коэффициент поправки размера для шрифта GOST_B
}