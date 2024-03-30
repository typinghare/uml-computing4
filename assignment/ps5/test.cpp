// Copyright 2024 James Chen

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <sstream>
#include <boost/test/unit_test.hpp>
#include "EDistance.hpp"

// Checks if `EDistance::penalty` works correctly.
BOOST_AUTO_TEST_CASE(testPenalty) {
    BOOST_REQUIRE_EQUAL(EDistance::penalty('a', 'a'), 0);
    BOOST_REQUIRE_EQUAL(EDistance::penalty('a', 'B'), 1);
}

// Checks if `EDistance::min3` works correctly.
BOOST_AUTO_TEST_CASE(testMin3) {
    BOOST_REQUIRE_EQUAL(EDistance::min3(5, 4, 3), 3);
    BOOST_REQUIRE_EQUAL(EDistance::min3(9, 12, 9), 9);
    BOOST_REQUIRE_EQUAL(EDistance::min3(-3, 6, 0), -3);
    BOOST_REQUIRE_EQUAL(EDistance::min3(7, 7, 7), 7);
}

// Checks if `EDistance::optDistance` works correctly; using the example in the instructions.
BOOST_AUTO_TEST_CASE(testOptDistance1) {
    EDistance eDistance{ "AACAGTTACC", "TAAGGTCA" };
    BOOST_REQUIRE_EQUAL(eDistance.optDistance(), 7);
}

// Checks if `EDistance::optDistance` works correctly; using 'endgaps7.txt'.
BOOST_AUTO_TEST_CASE(testOptDistance2) {
    EDistance eDistance{ "atattat", "tattata" };
    BOOST_REQUIRE_EQUAL(eDistance.optDistance(), 4);
}

// Checks if the return value of `EDistance::optDistance` the same as the summation of costs from
// `EDistance::alignment`; using the example in the instructions.
BOOST_AUTO_TEST_CASE(testAlignmentCostSum1) {
    EDistance eDistance{ "AACAGTTACC", "TAAGGTCA" };
    const auto editDistance = eDistance.optDistance();

    // Get the summation of costs
    int costSum = 0;
    std::istringstream istringstream(eDistance.alignment());
    std::string line;
    while (std::getline(istringstream, line)) {
        costSum += line.at(4) - '0';
    }

    BOOST_REQUIRE_EQUAL(editDistance, costSum);
}

// Checks if the return value of `EDistance::optDistance` the same as the summation of costs from
// `EDistance::alignment`; using 'endgaps7.txt'.
BOOST_AUTO_TEST_CASE(testAlignmentCostSum2) {
    EDistance eDistance{ "atattat", "tattata" };
    const auto editDistance = eDistance.optDistance();

    // Get the summation of costs
    int costSum = 0;
    std::istringstream istringstream(eDistance.alignment());
    std::string line;
    while (std::getline(istringstream, line)) {
        costSum += line.at(4) - '0';
    }

    BOOST_REQUIRE_EQUAL(editDistance, costSum);
}

// Checks if the two columns are correct. The first column should be the first string, while the
// second column should be the second string.
BOOST_AUTO_TEST_CASE(testAlignmentColumns) {
    static constexpr auto CHAR_GAP = '-';

    const std::string geneX = "AACAGTTACC";
    const std::string geneY = "TAAGGTCA";
    EDistance eDistance{ geneX, geneY };
    eDistance.optDistance();

    std::ostringstream geneXActual;
    std::ostringstream geneYActual;
    std::istringstream istringstream(eDistance.alignment());
    std::string line;
    while (std::getline(istringstream, line)) {
        const auto charX = line.at(0);
        const auto charY = line.at(2);
        if (charX != CHAR_GAP) {
            geneXActual << charX;
        }
        if (charY != CHAR_GAP) {
            geneYActual << charY;
        }
    }

    BOOST_REQUIRE_EQUAL(geneX, geneXActual.str());
    BOOST_REQUIRE_EQUAL(geneY, geneYActual.str());
}
