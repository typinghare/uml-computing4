cmake_minimum_required(VERSION 3.27)
project(computing4-uml)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "/opt/homebrew/opt/sfml")
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Assignments
add_executable(computing4-uml assignment/main.cpp)

add_executable(ps0 assignment/ps0/main.cpp)
target_link_libraries(ps0 sfml-graphics sfml-audio)

add_executable(playground-2d-array-pointer playground/2d-array-pointer.c)

