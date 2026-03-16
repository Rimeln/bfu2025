cmake_minimum_required(VERSION 3.19)
project(AuthApp_v2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

qt_standard_project_setup()

qt_add_executable(AuthApp_v2
    main.cpp
    mainwindow.cpp
    mainwindow.h
    logger.h
    filehandler.h
    userfilehandler.h
    photofilehandler.h
    photooperation.h
    uploadphoto.h
    deletephoto.h
    setavatarphoto.h
    choosephoto.h
)

target_link_libraries(AuthApp_v2
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Gui
)
