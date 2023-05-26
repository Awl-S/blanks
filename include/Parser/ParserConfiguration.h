#ifndef BLANKS_PARSERCONFIGURATION_H
#define BLANKS_PARSERCONFIGURATION_H

#include <string>
#include <vector>
#include <memory>
#include <filesystem>

/**
 * @class ParserConfiguration
 * @brief Класс для создания объекта конфигурации парсера.
 *
 * Класс ParserConfiguration предоставляет статический метод create() для создания объекта конфигурации парсера.
 * Объект конфигурации может быть создан на основе файла конфигурации формата JSON.
 */
class ParserConfiguration {
public:
    virtual ~ParserConfiguration() = default;

    /**
     * @brief Возвращает путь к файлу на основе указанного ключа.
     *
     * Метод возвращает путь к файлу, связанный с указанным ключом, из конфигурационного файла.
     *
     * @param key Ключ для поиска пути к файлу.
     * @return Путь к файлу.
     */
    virtual std::filesystem::path getFilePath(const std::string& key) = 0;

    /**
     * @brief Возвращает список файлов на основе указанного ключа и поискового запроса.
     *
     * Метод возвращает список файлов, связанных с указанным ключом и удовлетворяющих поисковому запросу, из конфигурационного файла.
     *
     * @param key Ключ для поиска списка файлов.
     * @param search Поисковый запрос для фильтрации файлов.
     * @return Список файлов.
     */
    virtual std::vector<std::filesystem::path> getFileList(const std::string& key, const std::string& search) = 0;

    /**
     * @brief Отображает информацию из конфигурационного файла.
     *
     * Метод отображает информацию из конфигурационного файла, используемого классом.
     * Данный метод может быть переопределен в производных классах.
     */
    virtual void display() = 0;

    /**
     * @brief Создает экземпляр класса ConfigParser на основе пути к конфигурационному файлу.
     *
     * Статический метод create() создает и возвращает экземпляр класса ConfigParser
     * на основе пути к конфигурационному файлу.
     *
     * @param config_file_path Путь к конфигурационному файлу.
     * @return Указатель на созданный экземпляр класса ConfigParser.
     */

/*
    static std::unique_ptr<ParserConfiguration> create(const std::string& config_file_path);
*/

    /**
 * @brief Создает объект конфигурации парсера на основе указанного файла.
 * @param config_file_path Путь к файлу конфигурации.
 * @return Указатель на объект конфигурации парсера.
 * @throws std::runtime_error Если тип файла не поддерживается.
 *
 * Статический метод create() создает объект конфигурации парсера на основе указанного файла конфигурации.
 * Если файл имеет расширение ".json", создается объект json, иначе выбрасывается исключение std::runtime_error.
 */

    /**
 * @brief Возвращает целочисленное значение, соответствующее заданному ключу.
 * @param key Ключ для получения целочисленного значения.
 * @return Целочисленное значение, соответствующее заданному ключу.
 * @throws std::runtime_error Если ключ отсутствует в конфигурации.
 *
 * Виртуальная функция getInteger() возвращает целочисленное значение,
 * соответствующее заданному ключу key. Данная функция должна быть реализована в классах-наследниках.
 * Если ключ отсутствует в конфигурации, выбрасывается исключение std::runtime_error.
 */
    virtual long long getInteger(const std::string &key);
};
#endif //BLANKS_PARSERCONFIGURATION_H