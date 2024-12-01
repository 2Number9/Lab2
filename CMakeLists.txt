cmake_minimum_required(VERSION 3.14)

# задаем используемый стандарт С++
set(CMAKE_CXX_STANDARD 17)

# TODO: переименовать проект
project(waw_parsing)

# задаем имя исполняемого файла основной программы
set(exe_name ${PROJECT_NAME})


# описываем основную библиотеку, т.е. библиотеку, содержащую все cpp-файлы, кроме main.cpp
# TODO: отредактировать список cpp-файлов
add_library(corelib OBJECT WawParser.cpp ConfigParser.cpp Converters.cpp)


# описываем исполняемый файл основной программы: это main.cpp + основная библиотека
add_executable(${exe_name} main.cpp)
target_link_libraries(${exe_name} corelib)