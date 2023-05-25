#include "../../include/RenderPDF/RenderPDF.h"


void RenderPDF::generatePDF(std::string &filename) {

    HPDF_Page page;
    size_t size_point_tbl = point_tbl.size();
    int blank = 0;
    int totalPage = 1;
    if(new_page){
        size_point_tbl/=2;
        totalPage = 2;
    }

    for(auto page_list = 0; page_list < totalPage; ++page_list) {
        if(page_list == 1) {
            pdf_ = HPDF_New(nullptr, nullptr);
            font_ = loadFont(fontPath_.string());

            size_point_tbl = point_tbl.size();
        }
        createA3Page();
        page = HPDF_GetCurrentPage(pdf_);
        for (; blank < size_point_tbl; blank++) {

            HPDF_Page_SetLineWidth(page, cfm_data_.digital_tick[1]);

            //test Удалить в конце, не рисуется
            if (false) {
                drawCircle(page, point_data_.coordinates[point_tbl[blank] - 1].first,
                           point_data_.coordinates[point_tbl[blank] - 1].second, cfm_data_.diameter / 2.0f);
            }

            // отрисовка круга
            if (false) {
                drawCircle(page, point_data_.coordinates[point_tbl[blank] - 1].first,
                           point_data_.coordinates[point_tbl[blank] - 1].second, zgt_data_.diameter / 2.0f);
            }

            //Центральный отверстие
            if (false) {
                drawCircle(page, point_data_.coordinates[point_tbl[blank] - 1].first,
                           point_data_.coordinates[point_tbl[blank] - 1].second,
                           zgt_data_.center_hole_diameter / 2.0f);
            }

            // Индексы не изменяются (исправить!!!)
            if(false){
                double xy, yz, radius;
                for (int i = 0; i < 2; ++i) {
                    xy = zgt_data_.mounting_holes[i * 3];
                    yz = zgt_data_.mounting_holes[i * 3 + 1];
                    yz = (yz > 0) ? -yz : abs(yz);
                    radius = zgt_data_.mounting_holes[i * 3 + 2] / 2.0f;

                    drawCircle(page, point_data_.coordinates[point_tbl[blank] - 1].first + xy,
                               point_data_.coordinates[point_tbl[blank] - 1].second + yz,
                               radius);
                }
            }

            generate_Marks(blank);
            drawMainLines(page, blank);

            drawDigitIndices(page, blank);
            drawAdditionalTicks(page, blank);
            marks.clear();

            generate_Marks(blank);
            drawMainLines(page, blank);

            drawDigitIndices(page, blank);
            drawAdditionalTicks(page, blank);
            marks.clear();
        }
        if(page_list == 1){
            filename+= "(" + std::to_string(page_list + 1) + ")";
        }
        HPDF_SaveToFile(pdf_, (filename + ".pdf").c_str());
    }
}