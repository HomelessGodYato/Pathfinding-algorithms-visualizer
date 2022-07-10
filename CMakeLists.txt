cmake_minimum_required(VERSION 3.21)
project(Pathfinder)

set(CMAKE_CXX_STANDARD 14)

add_executable(Pathfinder
        source/main.cpp
        source/Algorithm.cpp
        source/App.cpp
        source/ASTAR.cpp
        source/BFS.cpp
        source/DFS.cpp
        source/Graph.cpp
        source/Dijkstra.cpp
        source/Node.cpp
        source/RecMaze.cpp
        source/Search.cpp
        headers/Algorithm.h
        headers/App.h
        headers/ASTAR.h
        headers/BFS.h
        headers/DFS.h
        headers/Graph.h
        headers/Dijkstra.h
        headers/Node.h
        headers/RecMaze.h
        headers/Search.h
        imgui/imconfig-SFML.h
        imgui/imconfig.h
        imgui/imgui-SFML.cpp
        imgui/imgui-SFML.h
        imgui/imgui-SFML_export.h
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imgui_draw.cpp
        imgui/imgui_internal.h
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imguiStyle.h
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        )

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ./SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(D:/desktop/c++/Pathfinder/SFML-2.5.1/include)
include_directories(D:/desktop/c++/Pathfinder/imgui)
include_directories(D:/desktop/c++/Pathfinder/headers)
include_directories(D:/desktop/c++/Pathfinder/source)
target_link_libraries(Pathfinder sfml-system sfml-window sfml-graphics sfml-audio sfml-network)