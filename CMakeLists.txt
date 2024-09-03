cmake_minimum_required(VERSION 3.5)

project(life VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        headers/controller/cell.h
        headers/controller/game.h
        startstatewindowsettings.ui
        headers/controller/state.h
        src/controller/cell.cpp
        src/controller/game.cpp
        src/controller/state.cpp
        src/views/field.cpp
        headers/views/field.h
        src/views/mainwindow.cpp
        ui_mainwindow.h
        headers/views/mainwindow.h
        headers/views/createstatefield.h
        src/views/createstatefield.cpp
        createstatefield.ui
        ui_createstatefield.h
        mainwindow.ui
        headers/views/startstatewindowsettings.h
        ui_startstatewindowsettings.h
        src/views/startstatewindowsettings.cpp
        src/views/mainfieldwindow.cpp
        headers/views/mainfieldwindow.h
        ui_mainfieldwindow.h
        mainfieldwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(life
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET life APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(life SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(life
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(life PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(life PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS life
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(life)
endif()
