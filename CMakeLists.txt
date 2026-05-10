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
    src/View/mainwindow.cpp
    src/View/gridview.cpp
    src/View/Workspace/NodeView.cpp
    src/View/Workspace/EdgeView.cpp
    src/View/Workspace/CreateEdgeEvent.cpp
    src/View/editnodeview.cpp
    src/View/editedgeview.cpp
    src/Services/filemanager.cpp
    src/ViewModel/gridviewmodel.cpp
    src/Services/graphconnectioncheck.cpp
    src/View/graphcheck.cpp
    src/Services/dijkstra.cpp
    src/Model/distancematrix.cpp
    src/Services/pmedianevaluator.cpp
    src/Services/simulatedannealing.cpp
    src/Services/pmediansolver.cpp
    src/View/solutionview.cpp
    src/View/parameterview.cpp
)

set(HEADERS
    src/View/Workspace/NodeView.h
    src/View/mainwindow.h
    src/View/gridview.h
    src/View/Workspace/EdgeView.h
    src/View/Workspace/GridScene.h
    src/View/Workspace/CreateEdgeEvent.h
    src/View/editnodeview.h
    src/View/editedgeview.h
    src/Common/nodetype.h
    src/Common/dtos.h
    src/Common/idata.h
    src/Common/Builders/nodeviewbuilder.h
    src/Common/Builders/edgeviewbuilder.h
    src/Services/filemanager.h
    src/ViewModel/gridviewmodel.h
    src/Common/idmanager.h
    src/Services/graphconnectioncheck.h
    src/Model/node.h
    src/Common/Builders/nodebuilder.h
    src/Model/edge.h
    src/Common/Builders/edgebuilder.h
    src/View/graphcheck.h
    src/Services/dijkstra.h
    src/Model/distancematrix.h
    src/Services/pmedianevaluator.h
    src/Services/simulatedannealing.h
    src/Services/ievaluator.h
    src/Services/pmediansolver.h
    src/View/solutionview.h
    src/View/parameterview.h
)

set(VIEWS
    src/View/mainwindow.ui
)

qt_add_executable(PMedianProblem
    ${SOURCES}
    ${HEADERS}
    ${VIEWS}
)

target_link_libraries(PMedianProblem PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(PMedianProblem PRIVATE
    ${CMAKE_SOURCE_DIR}/src/View
)

set_target_properties(PMedianProblem PROPERTIES
    WIN32_EXECUTABLE TRUE
)