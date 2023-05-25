#ifndef BLANKS_PARSERCONFIGURATION_H
#define BLANKS_PARSERCONFIGURATION_H

#include <string>
#include <vector>
#include <memory>
#include <filesystem>

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
    [[maybe_unused]] virtual void display() = 0;

    /**
     * @brief Создает экземпляр класса ConfigParser на основе пути к конфигурационному файлу.
     *
     * Статический метод create() создает и возвращает экземпляр класса ConfigParser
     * на основе пути к конфигурационному файлу.
     *
     * @param config_file_path Путь к конфигурационному файлу.
     * @return Указатель на созданный экземпляр класса ConfigParser.
     */
    static std::unique_ptr<ParserConfiguration> create(const std::string& config_file_path);

    virtual long long getInteger(const std::string &key);
    };
#endif //BLANKS_PARSERCONFIGURATION_H