#include <stdexcept>
#include "../../include/RenderPDF/RenderPDF.h"

// Создание A3 страницы
void RenderPDF::createA3Page() {
    HPDF_Page page = HPDF_AddPage(pdf_);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A3, HPDF_PAGE_PORTRAIT);
}

// Function for loading font
HPDF_Font RenderPDF::loadFont(const std::string& fontPath) {
    auto font_name = HPDF_LoadTTFontFromFile(pdf_, fontPath.c_str(), HPDF_TRUE);
    auto font = HPDF_GetFont(pdf_, font_name, "CP1251");

    if(!font){
        throw std::runtime_error("Не удалось загрузить шрифт.");
    }

    return font;
}

RenderPDF::~RenderPDF() {
    if (pdf_) {
        HPDF_Free(pdf_);
    }
}

RenderPDF::RenderPDF(cfm cfm_data, zgt zgt_data, const std::vector<tbl> &tbl_data, nbr nbr_data, point point_data, std::filesystem::path fontPath) {
    initializeData(std::move(cfm_data), std::move(zgt_data), tbl_data, std::move(nbr_data), std::move(point_data), fontPath);
    initializePDF();
    adjustFontSize();
    font_ = loadFont(fontPath_.string());
    sortTblData();
    populatePointTbl();
    new_page = checkForNewPage();
}

// Private utility function for initializing data
void RenderPDF::initializeData(cfm cfm_data, zgt zgt_data, const std::vector<tbl> &tbl_data, nbr nbr_data, point point_data, std::filesystem::path fontPath) {
    cfm_data_ = std::move(cfm_data);
    zgt_data_ = std::move(zgt_data);
    tbl_data_ = tbl_data;
    nbr_data_ = std::move(nbr_data);
    point_data_ = std::move(point_data);
    fontPath_ = fontPath;
}

// Private utility function for initializing PDF
void RenderPDF::initializePDF() {
    pdf_ = HPDF_New(nullptr, nullptr);
    if(!pdf_){
        throw std::runtime_error("Не удалось создать PDF документ.");
    }
}

// Function for adjusting font size
void RenderPDF::adjustFontSize() {
    cfm_data_.digit_height*=1.090248; //коэффициент поправки размера для шрифта GOST_B
}