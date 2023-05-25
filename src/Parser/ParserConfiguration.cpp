#include "../../include/Parser/ParserConfiguration.h"
#include "../../include/Parser/json.h"

std::unique_ptr<ParserConfiguration> ParserConfiguration::create(const std::string& config_file_path) {
    if (config_file_path.ends_with(".json")) {
        return std::make_unique<json>(config_file_path);
    }
    else {
        throw std::runtime_error("Unsupported file type: " + config_file_path);
    }
}