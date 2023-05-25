#ifndef BLANKS_ENCODINGCONVERTER_H
#define BLANKS_ENCODINGCONVERTER_H
#include "string"
#include "vector"
#include "filesystem"

/**
 * @class EncodingConverter
 * @brief Класс для преобразования кодировки файлов.
 *
 * Конструктор класса принимает входной и выходной каталоги.
 * Если выходной каталог не указан, используется временный каталог.
 */
class EncodingConverter {
public:
    EncodingConverter(std::string  inputDir, const std::string& outputDir = "");
    void convert();
private:
    std::string inputDirectory;
    std::string outputDirectory;
    bool useTempDirectory;
    std::vector<std::string> fileExtensions;
    std::string sourceEncoding;
    std::string targetEncoding;
    size_t filesProcessed;
    size_t filesConverted;

    void loadSettings();
    void convertDirectory(const std::filesystem::path& dir);
    void convertFile(const std::filesystem::path& filepath);
    static bool iconvConvert(const std::string& input, std::string& output, const std::string& fromCharset, const std::string& toCharset);
    void printStats() const;
    static bool is_utf8(const std::string& str);
};
#endif //BLANKS_ENCODINGCONVERTER_H