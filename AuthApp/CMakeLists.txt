cmake_minimum_required(VERSION 3.19)
project(AuthApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(AuthApp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    logger.h
)

target_link_libraries(AuthApp
    PRIVATE
        Qt::Core
        Qt::Widgets
)
