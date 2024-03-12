cmake_minimum_required(VERSION 3.27)
project(computing4-uml)

set(CMAKE_CXX_STANDARD 17)

# Packages
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)
find_package(Boost 1.83 REQUIRED COMPONENTS unit_test_framework)

# ps0
add_executable(ps0
    assignment/ps0/main.cpp
)
target_link_libraries(ps0 sfml-graphics sfml-audio)

# ps1a
add_executable(ps1a
    assignment/ps1a/main.cpp
    assignment/ps1a/test.cpp
    assignment/ps1a/FibLFSR.cpp
    assignment/ps1a/FibLFSR.hpp
    assignment/ps1a/PhotoMagic.cpp
)
target_link_libraries(ps1a Boost::unit_test_framework)

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

# ps2
add_executable(ps2
    assignment/ps2/main.cpp
    assignment/ps2/PTree.hpp
    assignment/ps2/PTree.cpp
)
target_link_libraries(ps2 sfml-graphics)

# ps3
add_executable(ps3a
    assignment/ps3a/main.cpp
    assignment/ps3a/Sokoban.hpp
    assignment/ps3a/Sokoban.cpp
)
target_link_libraries(ps3a sfml-graphics)

# ps3b
add_executable(ps3b
    assignment/ps3b/main.cpp
    assignment/ps3b/Sokoban.hpp
    assignment/ps3b/Sokoban.cpp
    assignment/ps3b/SokobanConstants.hpp
    assignment/ps3b/InvalidCoordinateException.hpp
    assignment/ps3b/InvalidCoordinateException.cpp
    assignment/ps3b/SokobanElapsedTime.hpp
    assignment/ps3b/SokobanElapsedTime.cpp
    assignment/ps3b/SokobanScore.hpp
    assignment/ps3b/SokobanScore.cpp
    assignment/ps3b/SokobanTileGrid.hpp
    assignment/ps3b/SokobanTileGrid.cpp
    assignment/ps3b/SokobanPlayer.hpp
    assignment/ps3b/SokobanPlayer.cpp
)
target_link_libraries(ps3b -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lboost_unit_test_framework)

# ps3b test
add_executable(ps3b-test
    assignment/ps3b/test.cpp
    assignment/ps3b/Sokoban.hpp
    assignment/ps3b/Sokoban.cpp
    assignment/ps3b/SokobanConstants.hpp
    assignment/ps3b/InvalidCoordinateException.hpp
    assignment/ps3b/InvalidCoordinateException.cpp
    assignment/ps3b/SokobanElapsedTime.hpp
    assignment/ps3b/SokobanElapsedTime.cpp
    assignment/ps3b/SokobanScore.hpp
    assignment/ps3b/SokobanScore.cpp
    assignment/ps3b/SokobanTileGrid.hpp
    assignment/ps3b/SokobanTileGrid.cpp
    assignment/ps3b/SokobanPlayer.hpp
    assignment/ps3b/SokobanPlayer.cpp
)
target_link_libraries(ps3b-test -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lboost_unit_test_framework)

# ps4a
add_executable(ps4a
    assignment/ps4a/main.cpp
    assignment/ps4a/Universe.hpp
    assignment/ps4a/Universe.cpp
    assignment/ps4a/CelestialBody.hpp
    assignment/ps4a/CelestialBody.cpp
    assignment/ps4a/NBodyConstant.hpp
    assignment/ps4a/Common.hpp
    assignment/ps4a/Common.cpp
)
target_link_libraries(ps4a -lsfml-graphics -lsfml-audio)

# ps4a test
add_executable(ps4a-test
    assignment/ps4a/test.cpp
    assignment/ps4a/Universe.hpp
    assignment/ps4a/Universe.cpp
    assignment/ps4a/CelestialBody.hpp
    assignment/ps4a/CelestialBody.cpp
    assignment/ps4a/NBodyConstant.hpp
    assignment/ps4a/Common.hpp
    assignment/ps4a/Common.cpp
)
target_link_libraries(ps4a -lsfml-graphics -lsfml-window -lsfml-system -lboost_unit_test_framework)

# ps4b
add_executable(ps4b
    assignment/ps4b/main.cpp
    assignment/ps4b/NBodyConstant.hpp
    assignment/ps4b/Universe.hpp
    assignment/ps4b/Universe.cpp
    assignment/ps4b/CelestialBody.hpp
    assignment/ps4b/CelestialBody.cpp
)
target_link_libraries(ps4b -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system)

# playground
add_executable(playground-any playground/any.cpp)
add_executable(playground-size playground/size.cpp)
add_executable(bitwise-test playground/bitwise-test.cpp
    assignment/ps4b/NBodyConstant.hpp
    assignment/ps4b/Universe.cpp
    assignment/ps4b/Universe.hpp
    assignment/ps4b/CelestialBody.cpp
    assignment/ps4b/CelestialBody.hpp)
add_executable(rand-between playground/rand-between.cpp)
add_executable(swap playground/swap.cpp)
add_executable(findMode playground/find-mode.cpp)