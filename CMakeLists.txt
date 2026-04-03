cmake_minimum_required(VERSION 3.16)

project(PMedianProblem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Widgets
)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Widgets
)

set(SOURCES
    src/main.cpp
)

set(VIEWS
    src/View/mainwindow.cpp
    src/View/mainwindow.h
    src/View/mainwindow.ui
)

qt_add_executable(PMedianProblem
    ${SOURCES}
    ${VIEWS}
    src/View/Components/grid.h src/View/Components/grid.cpp
    src/View/Workspace/SelectionManager.h
)

target_link_libraries(PMedianProblem PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

set_target_properties(PMedianProblem PROPERTIES
    WIN32_EXECUTABLE TRUE
)