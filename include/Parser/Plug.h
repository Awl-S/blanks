#ifndef BLANKS_PLUG_H
#define BLANKS_PLUG_H

#include <string>
#include "ParserConfiguration.h"
#include "json.h"

namespace parser{
    static std::unique_ptr<ParserConfiguration> create(const std::string& config_file_path) {
        if (config_file_path.ends_with(".json")) {
            return std::make_unique<json>(config_file_path);
        }
        else {
            throw std::runtime_error("Unsupported file type: " + config_file_path);
        }
    }
}


#endif //BLANKS_PLUG_H
