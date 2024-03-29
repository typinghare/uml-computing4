// Copyright 2024 James Chen

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

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
