cmake_minimum_required(VERSION 3.27)
project(sokoban_remake)
set(CMAKE_CXX_STANDARD 20)

add_executable(sokoban
        src/main.cpp
        src/Sokoban.hpp
        src/Sokoban.cpp
)
target_link_libraries(sokoban sfml-system sfml-graphics sfml-window sfml-audio)