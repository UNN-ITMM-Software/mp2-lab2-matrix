cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(PROJECT_NAME mp2-lab2-matrix)
project(${PROJECT_NAME})#название проекта

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/LibImage) #Добавляем директорию "${CMAKE_CURRENT_SOURCE_DIR}/LibImage" в дополняемые каталоги включаемых файлов
#${CMAKE_CURRENT_SOURCE_DIR} - стандартная переменная с адресом рабочей директории

add_subdirectory(include)
add_subdirectory(samples)#основной исполняемый файл
add_subdirectory(gtest)#библиотека тестирования
add_subdirectory(test)#создает ещё один исполняемый файл с самими тестами