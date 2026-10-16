cmake_minimum_required(VERSION 3.16)
project(QtTranslatorApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

add_executable(QtTranslatorApp
    main.cpp
    TranslatorWidget.h
    TranslatorWidget.cpp
)

target_link_libraries(QtTranslatorApp PRIVATE Qt6::Widgets Qt6::Network)