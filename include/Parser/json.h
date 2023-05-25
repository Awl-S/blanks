#ifndef BLANKS_JSON_H
#define BLANKS_JSON_H

#include <nlohmann/json.hpp>
#include "ParserConfiguration.h"

class json: public ParserConfiguration{
public:
    void display() override;

    explicit json(const std::string& config_file_path);

    std::filesystem::path getFilePath(const std::string& key) override;

    std::vector<std::filesystem::path> getFileList(const std::string& key, const std::string& search) override;

    long long getInteger(const std::string &key);

private:
    nlohmann::json config_json;
};
#endif //BLANKS_JSON_H