#include "../../include/RenderPDF/RenderPDF.h"

/**
 * @brief Создает PDF-документ, используя графические элементы, определенные в других методах класса.
 *
 * @param filename Ссылка на строку, содержащую имя будущего файла PDF. Если будет создано несколько страниц, то функция модифицирует эту строку, добавляя номер каждой страницы.
 *
 * Она создает страницы формата A3 и на каждой странице рисует набор элементов, таких как основные линии, индексы и дополнительные отметки, для каждого элемента в таблице точек (`point_tbl`).
 * Генерация этих элементов осуществляется с помощью функций `generate_Marks`, `drawMainLines`, `drawDigitIndices` и `drawAdditionalTicks`. Эти функции используют данные из других членов класса, таких как `cfm_data_` и `zgt_data_`.
 * В конце, документ сохраняется в файл с указанным именем.
 */
void RenderPDF::generatePDF(std::string &filename, std::vector<std::string> args) {

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
            if (args[0] == "true") {
                drawCircle(page, point_data_.coordinates[point_tbl[blank] - 1].first,
                           point_data_.coordinates[point_tbl[blank] - 1].second, zgt_data_.diameter / 2.0f);
            }

            //Центральный отверстие
            if (args[1] == "true") {
                drawCircle(page, point_data_.coordinates[point_tbl[blank] - 1].first,
                           point_data_.coordinates[point_tbl[blank] - 1].second,
                           zgt_data_.center_hole_diameter / 2.0f);
            }

            // Индексы не изменяются
            if(args[2] == "true"){
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