#include "../../include/converting/EncodingConverter.h"
#include "iostream"
#include <utility>
#include "iconv.h"
#include "filesystem"
#include "fstream"

/**
 * @brief Конструктор объекта EncodingConverter.
 *
 * @param inputDir Входной каталог.
 * @param outputDir Выходной каталог.
 *
 * Если outputDir пуст, используется временный каталог.
 * Загружает настройки преобразования кодировки и сбрасывает счетчики файлов.
 */
EncodingConverter::EncodingConverter(std::string inputDir, const std::string& outputDir)
        : inputDirectory(std::move(inputDir)), outputDirectory(outputDir), useTempDirectory(outputDir.empty()) {
    loadSettings(), filesConverted = 0, filesProcessed = 0;
}

/**
 * @brief Загружает настройки преобразования кодировки.
 *
 * Устанавливает исходную кодировку в "UTF-8" и целевую кодировку в "WINDOWS-1251".
 * Задает расширения файлов, которые следует преобразовывать.
 */
void EncodingConverter::loadSettings(){
    sourceEncoding = "WINDOWS-1251";
    targetEncoding = "UTF-8";

    // Создаем массив итераторов на строки, которые нужно добавить
    std::string extensions[] = { ".tbl", ".нбр", ".згт", ".cfm" };
    size_t numExtensions = sizeof(extensions) / sizeof(extensions[0]);

    // Используем конструктор std::vector, принимающий два итератора
    fileExtensions.insert(fileExtensions.end(), extensions, extensions + numExtensions);
}

/**
 * @brief Конвертирует файлы в директории.
 *
 * Метод конвертирует файлы в указанной директории и выводит статистику по конвертированным файлам.
 * Путь к директории, содержащей исходные файлы, задается в переменной inputDirectory.
 */
void EncodingConverter::convert() {
    std::filesystem::path inputPath(inputDirectory);
    convertDirectory(inputPath);
    printStats();
}

/**
 * @brief Конвертирует файлы в указанной директории и её поддиректориях.
 *
 * Метод рекурсивно конвертирует все файлы в указанной директории и её поддиректориях.
 * Конвертируемые файлы должны иметь расширения, указанные в списке fileExtensions.
 * Если файл имеет другое расширение и outputDirectory указана, он будет скопирован в указанную выходную директорию.
 *
 * @param dir Путь к директории, в которой нужно выполнить конвертацию файлов.
 */
void EncodingConverter::convertDirectory(const std::filesystem::path& dir) {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            filesProcessed++;
            std::filesystem::path relativePath = std::filesystem::relative(entry, inputDirectory);
            std::filesystem::path outputPath = useTempDirectory ? std::filesystem::temp_directory_path() / relativePath : outputDirectory / relativePath;

            if (std::find(fileExtensions.begin(), fileExtensions.end(), entry.path().extension()) != fileExtensions.end()) {
                convertFile(entry.path());
            } else if (!outputDirectory.empty()) {
                // Если файл имеет другое расширение и outputDirectory указана, копируем его
                std::filesystem::create_directories(outputPath.parent_path());
                std::filesystem::copy_file(entry, outputPath, std::filesystem::copy_options::overwrite_existing);
            }
        }
    }
}

/**
 * @brief Конвертирует строку из одной кодировки в другую с помощью iconv.
 *
 * Метод конвертирует строку из одной кодировки в другую с использованием функций iconv.
 *
 * @param input Входная строка для конвертации.
 * @param output Строка, в которую будет записан результат конвертации.
 * @param fromCharset Исходная кодировка.
 * @param toCharset Целевая кодировка.
 * @return true, если конвертация прошла успешно, иначе false.
 */
bool EncodingConverter::iconvConvert(const std::string& input, std::string& output, const std::string& fromCharset, const std::string& toCharset) {
    iconv_t cd = iconv_open(toCharset.c_str(), fromCharset.c_str());
    if (cd == (iconv_t)-1) {
        perror("iconv_open");
        return false;
    }

    std::vector<char> inBuf(input.begin(), input.end());
    size_t inLeft = inBuf.size();
    size_t outLeft = inLeft * 4;
    std::vector<char> outBuf(outLeft);

    char* inPtr = inBuf.data();
    char* outPtr = outBuf.data();

    while (inLeft > 0) {
        size_t result = iconv(cd, &inPtr, &inLeft, &outPtr, &outLeft);
        if (result == (size_t)-1) {
            iconv_close(cd);
            return false;
        }
    }

    iconv_close(cd);
    outBuf.resize(outBuf.size() - outLeft);

    output.assign(outBuf.begin(), outBuf.end());
    return true;
}

/**
 * @brief Конвертирует содержимое файла из одной кодировки в другую и сохраняет результат в файл.
 *
 * Метод читает содержимое файла с указанным путем, конвертирует его из исходной кодировки в целевую и сохраняет результат в файл.
 * Если включена опция useTempDirectory, то промежуточный файл будет создан во временной директории, а затем скопирован и заменит исходный файл.
 *
 * @param filepath Путь к файлу, который нужно конвертировать.
 */
void EncodingConverter::convertFile(const std::filesystem::path& filepath) {
    std::cout << filepath << std::endl;
    std::ifstream inFile(filepath, std::ios::binary);
    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

    std::filesystem::path relativePath = std::filesystem::relative(filepath, inputDirectory);
    std::filesystem::path outputPath = useTempDirectory ? std::filesystem::temp_directory_path() / relativePath : outputDirectory / relativePath;
    std::filesystem::create_directories(outputPath.parent_path());

    if (!is_utf8(content)) {
        std::string utf8Content;
        if (iconvConvert(content, utf8Content, sourceEncoding, targetEncoding)) {
            content = utf8Content;
            filesConverted++;
        } else {
            std::cerr << "Error Converting file '" << filepath << "': Invalid or incomplete multibyte or wide character" << std::endl;
        }
    }

    std::ofstream outFile(outputPath, std::ios::binary);
    outFile.write(content.data(), content.size());
    outFile.close();

    if (useTempDirectory) {
        std::filesystem::copy(outputPath, filepath, std::filesystem::copy_options::overwrite_existing);
        std::filesystem::remove(outputPath);
    }
}

/**
 * @brief Выводит статистику по конвертированным файлам.
 *
 * Метод выводит информацию о количестве обработанных и конвертированных файлов.
 */
void EncodingConverter::printStats() const {
    std::cout << "Files processed: " << filesProcessed << std::endl;
    std::cout << "Files converted: " << filesConverted << std::endl;
}

/**
 * @brief Проверяет, является ли строка в кодировке UTF-8.
 *
 * Метод проверяет, является ли строка в кодировке UTF-8 путем анализа байтовой последовательности.
 * Возвращает true, если строка является корректной UTF-8 строкой, иначе false.
 *
 * @param str Строка, которую нужно проверить.
 * @return true, если строка является корректной UTF-8 строкой, иначе false.
 */
bool EncodingConverter::is_utf8(const std::string &str) {
    size_t length = str.size();
    for (size_t i = 0; i < length; ) {
        if ((str[i] & 0x80) == 0) {
            i += 1;
        } else if ((str[i] & 0xE0) == 0xC0 && i + 1 < length && (str[i + 1] & 0xC0) == 0x80) {
            i += 2;
        } else if ((str[i] & 0xF0) == 0xE0 && i + 2 < length && (str[i + 1] & 0xC0) == 0x80 && (str[i + 2] & 0xC0) == 0x80) {
            i += 3;
        } else if ((str[i] & 0xF8) == 0xF0 && i + 3 < length && (str[i + 1] & 0xC0) == 0x80 && (str[i + 2] & 0xC0) == 0x80 && (str[i + 3] & 0xC0) == 0x80) {
            i += 4;
        } else {
            return false;
        }
    }
    return true;
}