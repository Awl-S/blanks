cmake_minimum_required(VERSION 3.25)
project(blanks)

set(CMAKE_CXX_STANDARD 23)
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")

set(VCPKG_TARGET_TRIPLET "x64-windows-static"
        CACHE STRING "Vcpkg target triplet to use")
message("VCPKG_TARGET_TRIPLET: " ${VCPKG_TARGET_TRIPLET})

if(MSVC)
    target_link_libraries(blanks PRIVATE RuntimeObject)
endif()

add_executable(blanks main.cpp src/CommandLine/CommandLine.cpp include/CommandLine/CommandLine.h src/Converting/EncodingConverter.cpp include/Converting/EncodingConverter.h src/Reader/FileReader.cpp include/Reader/FileReader.h include/Reader/FileReader.h include/Reader/FileReader.h src/Reader/textReader.cpp include/Reader/textReader.h include/struct/cfm.h include/struct/nbr.h include/struct/point_data.h include/struct/tbl.h include/struct/zgt.h src/RenderPDF/RenderPDF.cpp include/RenderPDF/RenderPDF.h src/RenderPDF/Line.cpp src/RenderPDF/Processor.cpp src/RenderPDF/draw.cpp src/RenderPDF/Print.cpp src/Parser/ParserConfiguration.cpp include/Parser/ParserConfiguration.h src/Parser/json.cpp include/Parser/json.h src/Generated/Generated.cpp include/Generated/Generated.h src/RenderPDF/digit.cpp)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(blanks PRIVATE nlohmann_json::nlohmann_json)

find_package(Iconv)
target_link_libraries(blanks PRIVATE Iconv::Iconv)

find_package(unofficial-libharu CONFIG REQUIRED)
target_link_libraries(blanks PRIVATE unofficial::libharu::hpdf)
