#ifndef BLANKS_TEXTREADER_H
#define BLANKS_TEXTREADER_H

#include <regex>
#include "FileReader.h"
#include "../struct/nbr.h"
#include "../struct/point_data.h"
#include "../struct/tbl.h"
#include "../struct/cfm.h"
#include "../struct/zgt.h"

class textReader : public FileReader {
public:
    explicit textReader(const std::filesystem::path& file_path) : FileReader(file_path) {}

    void read_nbr(nbr& data);

    void read_point(point& data);

    void read_tbl(tbl& data);

    void read_cfm(cfm& data);

    void read_zgt(zgt& data);
};
#endif //BLANKS_TEXTREADER_H