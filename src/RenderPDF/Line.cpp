#include <cmath>

#include "../../include/RenderPDF/RenderPDF.h"

/**
 * @brief Генерирует маркеры на основе измерений из данных таблицы.
 *
 * @param blank Индекс строки в таблице данных, из которой следует сгенерировать маркеры.
 */
void RenderPDF::generate_Marks(size_t blank) {
    size_t size = tbl_data_[blank].measurements.size();
    auto a0 = (tbl_data_[blank].measurements[0][0] + tbl_data_[blank].measurements[0][1]) / 2.0;
    auto an =
            (tbl_data_[blank].measurements[size - 1][0] + tbl_data_[blank].measurements[size - 1][1]) / 2.0;
    auto aDelta = (an - a0) / size;

    for (int i = 0; i < size; i++) {
        auto asred = (tbl_data_[blank].measurements[i][0] + tbl_data_[blank].measurements[i][1]) / 2.0;
        marks.push_back(asred + aDelta);
    }
    std::vector<double> angles_deg(marks.size());

    // Конвертация углов из радиан в градусы
    for (size_t i = 0; i < marks.size(); i++) {
        angles_deg[i] = marks[i] * (180.0 / PI);
    }

    double a0_deg = angles_deg.front();
    double an_deg = angles_deg.back();

    // Вычисление добавочного угла \Delta
    double delta = (360.0 - an_deg - a0_deg) / 2;

    // Пересчет углов с использованием \Delta
    std::vector<double> new_angles_deg(angles_deg.size());
    for (size_t i = 0; i < angles_deg.size(); i++) {
        new_angles_deg[i] = angles_deg[i] + delta;
    }

    // Конвертация углов обратно в радианы
    for (size_t i = 0; i < new_angles_deg.size(); i++) {
        marks[i] = new_angles_deg[i] * (PI / 180.0);
    }
}

/**
 * @brief Рисует основные линии на странице PDF.
 *
 * @param page Страница PDF, на которой будут нарисованы основные линии.
 * @param blank Индекс строки в таблице данных, на основе которой следует рисовать линии.
 */
void RenderPDF::drawMainLines(HPDF_Page page, size_t blank) {
    //Рисуем линии главные
    double radius = cfm_data_.diameter / 2.0;
    size_t i = 0;
    for (double angle: marks) {
        angle = 4.71239 - angle;

        double sinAngle = sin(angle);
        double cosAngle = cos(angle);
        HPDF_REAL x1, x2, y1, y2;

        x1 = point_data_.coordinates[point_tbl[blank] - 1].first +
             (radius - cfm_data_.digital_tick[0]) * cosAngle;
        y1 = point_data_.coordinates[point_tbl[blank] - 1].second +
             (radius - cfm_data_.digital_tick[0]) * sinAngle;

        if (i == 0) { // Если это первая итерация, сместить верхнюю линию на 90 градусов
            double shift_angle = angle + 1.5708; // Смещение на 90 градусов вправо
            double center_offset = cfm_data_.digital_tick[2] / 2; // Размер центра

            x1 = point_data_.coordinates[point_tbl[blank] - 1].first +
                 (radius - cfm_data_.digital_tick[0]) * cosAngle;
            y1 = point_data_.coordinates[point_tbl[blank] - 1].second +
                 (radius - cfm_data_.digital_tick[0]) * sinAngle;

            x1 -= center_offset * cos(shift_angle); // Смещение x координаты
            y1 -= center_offset * sin(shift_angle); // Смещение y координаты

            x2 = x1 + (cfm_data_.digital_tick[0] - cfm_data_.digital_tick[2]) *
                      cos(shift_angle); // Правая часть линии
            y2 = y1 + (cfm_data_.digital_tick[0] - cfm_data_.digital_tick[2]) *
                      sin(shift_angle); // Правая часть линии
        } else {
            x2 = point_data_.coordinates[point_tbl[blank] - 1].first +
                 (radius - cfm_data_.digital_tick[2]) * cosAngle;
            y2 = point_data_.coordinates[point_tbl[blank] - 1].second +
                 (radius - cfm_data_.digital_tick[2]) * sinAngle;
        }

        // Верняя линия
        HPDF_Page_SetLineWidth(page, cfm_data_.digital_tick[3]);

        draw_line(page, x2, y2, x1, y1);

        // Нижняя линия
        x1 = point_data_.coordinates[point_tbl[blank] - 1].first + radius * cos(angle);
        y1 = point_data_.coordinates[point_tbl[blank] - 1].second + radius * sin(angle);
        x2 = point_data_.coordinates[point_tbl[blank] - 1].first +
             (radius - cfm_data_.digital_tick[2]) * cosAngle;
        y2 = point_data_.coordinates[point_tbl[blank] - 1].second +
             (radius - cfm_data_.digital_tick[2]) * sinAngle;

        if (i == 0) {
            x2 = point_data_.coordinates[point_tbl[blank] - 1].first +
                 (radius - cfm_data_.digital_tick[0]) * cosAngle;
            y2 = point_data_.coordinates[point_tbl[blank] - 1].second +
                 (radius - cfm_data_.digital_tick[0]) * sinAngle;
        }

        HPDF_Page_SetLineWidth(page, cfm_data_.digital_tick[1]);
        draw_line(page, x2, y2, x1, y1);

        i++;
    }
}


/**
 * @brief Рисует дополнительные отметки на странице PDF.
 *
 * @param page Страница PDF, на которой будут нарисованы дополнительные отметки.
 * @param blank Индекс строки в таблице данных, на основе которой следует рисовать отметки.
 */
void RenderPDF::drawAdditionalTicks(HPDF_Page page, size_t blank) {
    auto radius = cfm_data_.diameter / 2.0f;
    size_t size_tick_mask = cfm_data_.tick_mask.size() - 1;
    for (size_t k = 0; k < marks.size() - 1; k++) {
        double angle1 = 4.71239 - marks[k];
        double angle2 = 4.71239 - marks[k + 1];
        double angle_diff = (angle2 - angle1) / double(size_tick_mask);

        for (size_t j = 1; j <= size_tick_mask; j++) {
            double angle = angle1 + j * angle_diff;
            HPDF_REAL x1 = point_data_.coordinates[point_tbl[blank] - 1].first + radius * cos(angle);
            HPDF_REAL y1 = point_data_.coordinates[point_tbl[blank] - 1].second + radius * sin(angle);
            HPDF_REAL x2, y2;
            HPDF_REAL height_line;

            if (cfm_data_.tick_mask[j] == '1') {
                height_line = cfm_data_.small_tick[0];
            }
            if (cfm_data_.tick_mask[j] == '2') {
                height_line = cfm_data_.big_tick[0];
            }
            if (cfm_data_.tick_mask[j] == '3') {
                height_line = cfm_data_.digital_tick[0];
            }

            x2 = point_data_.coordinates[point_tbl[blank] - 1].first + (radius - height_line) * cos(angle);
            y2 = point_data_.coordinates[point_tbl[blank] - 1].second + (radius - height_line) * sin(angle);

            draw_line(page, x1, y1, x2, y2);
        }
    }
}
