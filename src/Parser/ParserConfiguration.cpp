#include "../../include/Parser/ParserConfiguration.h"
#include "../../include/Parser/json.h"

/**
 * @brief Создает объект конфигурации парсера на основе указанного файла.
 * @param config_file_path Путь к файлу конфигурации.
 * @return Указатель на объект конфигурации парсера.
 * @throws std::runtime_error Если тип файла не поддерживается.
 *
 * Статический метод create() создает объект конфигурации парсера на основе указанного файла конфигурации.
 * Если файл имеет расширение ".json", создается объект json, иначе выбрасывается исключение std::runtime_error.
 */
std::unique_ptr<ParserConfiguration> ParserConfiguration::create(const std::string& config_file_path) {
    if (config_file_path.ends_with(".json")) {
        return std::make_unique<json>(config_file_path);
    }
    else {
        throw std::runtime_error("Unsupported file type: " + config_file_path);
    }
}