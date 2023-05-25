#include <iostream>
#include "include/Converting/EncodingConverter.h"
#include "include/CommandLine/CommandLine.h"
#include "include/struct/cfm.h"
#include "include/struct/zgt.h"
#include "include/Reader/textReader.h"
#include "include/Generated/Generated.h"
#include "include/Parser/ParserConfiguration.h"
#include "include/RenderPDF/RenderPDF.h"

void print_duration(const auto& start) {
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    auto duration_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Время выполнения: " << duration_microseconds.count() << " microseconds" << std::endl;
    std::cout << "Время выполнения: " << duration_milliseconds.count() << " milliseconds" << std::endl;
}

std::filesystem::path find_file_by_name(const std::filesystem::path& directory, std::string& model_name, const std::string& extension) {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            const auto& file_name = entry.path().filename().string();
            const auto& file_extension = entry.path().extension().string();
            if (file_name == model_name + file_extension && file_extension == extension) {
                std::filesystem::path path_str = entry.path();
                //std::replace(path_str.string().begin(), path_str.string().end(), '\\', '/');
                return path_str;
            }
        }
    }
    throw std::runtime_error("File not found: " + model_name);
}

std::string getCurrentDateTime() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    char dateTimeString[20];
    std::strftime(dateTimeString, sizeof(dateTimeString), "%Y-%m-%d_%H-%M-%S", localTime);

    return std::string(dateTimeString);
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    auto start = std::chrono::high_resolution_clock::now();
    {
        CommandLine cmd(argc, argv);
        auto command_type = cmd.get_command_type();
        auto args = cmd.get_args();

        //УДАЛИТЬ
        if(command_type == CommandLine::CommandType::UNKNOWN){
            auto config_parser = ParserConfiguration::create("C:/GenerateBlank/path/path.json");
            const auto debug = config_parser->getInteger("debug");

            auto tbl_directory = config_parser->getFilePath("tbl");
            auto tbl_files = config_parser->getFileList("tbl", "scale");
            std::vector<tbl> tbl_data;
            for (auto& tbl_file : tbl_files) {
                std::cout << "Чтение TBL:\t" << tbl_file << std::endl;
                tbl temp_tbl;
                textReader(tbl_file).read_tbl(temp_tbl);
                tbl_data.push_back(temp_tbl);
                if(debug){
                    temp_tbl.display();
                }
            }

            auto cfm_file = config_parser->getFilePath("cfm");
            auto cfm_file_path = find_file_by_name(cfm_file, tbl_data[0].model, ".cfm");
            std::cout << "Чтение CFM:\t" << cfm_file_path << std::endl;
            cfm cfm_data;
            textReader(cfm_file_path).read_cfm(cfm_data);
            if(debug){
                cfm_data.display();
            }

            auto point_file = config_parser->getFilePath("point");
            auto point_file_path = find_file_by_name(point_file, tbl_data[0].model, ".point");
            std::cout << "Чтение набора точек:\t" << point_file_path << std::endl;
            point point_data;
            textReader(point_file_path).read_point(point_data);
            if(debug){
                point_data.display();
            }

            auto zgt_file = config_parser->getFilePath("zgt");
            auto zgt_file_path = find_file_by_name(zgt_file, cfm_data.blank, ".згт");
            std::cout << "Чтение заготовок:\t" << zgt_file_path << std::endl;
            zgt zgt_data;
            textReader(zgt_file_path).read_zgt(zgt_data);
            if(debug){
                zgt_data.display();
            }
            //std::cout << "Чтение наборов изображений:\t" << nbr_file_path << std::endl;
            auto nbr_file = config_parser->getFilePath("nbr");
            //auto nbr_file_path = find_file_by_name(zgt_file, cfm_data.blank, ".нбр");
            nbr nbr_data;
            //textReader(nbr_file_path).read_nbr(nbr_data);
            if(debug == 0){
            }

                RenderPDF pdf(cfm_data, zgt_data, tbl_data, nbr_data, point_data, config_parser->getFilePath("fontPath"));
            std::string filename = getCurrentDateTime() + "(" + cfm_data.blank + ")";
            pdf.generatePDF(filename);
            print_duration(start);
            return 0;
        }

        if(command_type == CommandLine::CommandType::GEN){
            Generated gen;
            gen.generateJsonFile("setting.json");
        }

        if(command_type == CommandLine::CommandType::UNKNOWN){
            print_duration(start);
            std::cout << "Неизвестная команда\n";
            return -1;
        }

        if(command_type == CommandLine::CommandType::CONVERT){
            if(args.size() == 1){
                EncodingConverter converter(args[0]);
                converter.convert();
            } else if (args.size() == 2) {
                EncodingConverter converter(args[0], args[1]);
                converter.convert();
            } else {
                std::cerr << "Неверное количество аргументов." << std::endl;
                return 1;
            }
        }

        if(CommandLine::CommandType::PRINT == command_type){
            auto config_parser = ParserConfiguration::create(args[0]);


        }

    }

    print_duration(start);
}