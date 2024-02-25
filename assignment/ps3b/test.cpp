// Copyright 2024 James Chen

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <boost/test/unit_test.hpp>
#include "Sokoban.hpp"

BOOST_AUTO_TEST_CASE(testHeightWidth) {
    SB::Sokoban sokoban;
    std::ifstream ifstream{ "assets/level/level2.lvl" };
    ifstream >> sokoban;

    BOOST_REQUIRE_EQUAL(sokoban.height(), 10);
    BOOST_REQUIRE_EQUAL(sokoban.width(), 12);
}

BOOST_AUTO_TEST_CASE(testPlayerPosition1) {
    SB::Sokoban sokoban;
    std::ifstream ifstream{ "assets/level/level2.lvl" };
    ifstream >> sokoban;

    const auto playerLoc = sokoban.playerLoc();
    BOOST_REQUIRE_EQUAL(playerLoc.x, 8);
    BOOST_REQUIRE_EQUAL(playerLoc.y, 5);
}

BOOST_AUTO_TEST_CASE(testPlayerPosition2) {
    SB::Sokoban sokoban;
    std::ifstream ifstream{ "assets/level/level2.lvl" };
    ifstream >> sokoban;

    // Move upward, since there are two boxes, the player should not move
    sokoban.movePlayer(SB::Direction::Up);
    const auto playerLoc = sokoban.playerLoc();
    BOOST_REQUIRE_EQUAL(playerLoc.x, 8);
    BOOST_REQUIRE_EQUAL(playerLoc.y, 5);
}

BOOST_AUTO_TEST_CASE(testPlayerPosition3) {
    SB::Sokoban sokoban;
    std::ifstream ifstream{ "assets/level/level2.lvl" };
    ifstream >> sokoban;

    // Move rightward twice. For the first move, the player pushes the box rightawrds;
    // For the second move, the player saty on the pot, as the box cannot be pushed
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    BOOST_REQUIRE_EQUAL(sokoban.playerLoc().x, 9);
    BOOST_REQUIRE_EQUAL(sokoban.playerLoc().y, 5);
    // const char tileChar = static_cast<char>(sokoban.getTileChar({ 10, 5 }));
    // BOOST_REQUIRE_EQUAL(tileChar, 'A');
}
