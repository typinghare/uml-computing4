cmake_minimum_required(VERSION 3.27)
project(computing4-uml)

set(CMAKE_CXX_STANDARD 17)

# Packages
include_directories(/opt/homebrew/include)
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)
find_package(Boost 1.83 REQUIRED COMPONENTS unit_test_framework)

# ps1b
add_executable(ps1b
        assignment/ps1b/PhotoMagic.hpp
        assignment/ps1b/PhotoMagic.cpp
        assignment/ps1b/FibLFSR.hpp
        assignment/ps1b/FibLFSR.cpp
        assignment/ps1b/main.cpp
        assignment/ps1b/test.cpp
)
target_link_libraries(ps1b sfml-graphics sfml-audio Boost::unit_test_framework)

# ps0
add_executable(ps0
        assignment/ps0/main.cpp
)
target_link_libraries(ps0 sfml-graphics sfml-audio)

# ps1a

add_executable(ps1a
        assignment/ps1a/test.cpp
        assignment/ps1a/FibLFSR.cpp
        assignment/ps1a/FibLFSR.hpp
        assignment/ps1a/PhotoMagic.cpp
)
target_link_libraries(ps1a Boost::unit_test_framework)

# playground
add_executable(playground-2d-array-pointer playground/size.cpp)
add_executable(playground-size playground/size.cpp)
add_executable(bitwise-test playground/bitwise-test.cpp)
add_executable(rand-between playground/rand-between.cpp)