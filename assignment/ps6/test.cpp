// Copyright 2024 James Chen

// Checks if `EDistance::penalty` works correctly.

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <sstream>
#include <boost/test/unit_test.hpp>
#include "RandWriter.hpp"

// Checks if `RandWriter::freq(const std::string&)` works correctly.
BOOST_AUTO_TEST_CASE(testFreq1) {
    const RandWriter randWriter{ "gagggagaggcgagaaa", 2 };
    BOOST_REQUIRE_EQUAL(randWriter.freq("ga"), 5);
    BOOST_REQUIRE_EQUAL(randWriter.freq("ag"), 5);
    BOOST_REQUIRE_EQUAL(randWriter.freq("gg"), 3);
    BOOST_REQUIRE_EQUAL(randWriter.freq("gc"), 1);
    BOOST_REQUIRE_EQUAL(randWriter.freq("cg"), 1);
    BOOST_REQUIRE_EQUAL(randWriter.freq("aa"), 2);
}

// Checks if `RandWriter::freq(const std::string&, char)` works correctly.
BOOST_AUTO_TEST_CASE(testFreq2) {
    const RandWriter randWriter{ "gagggagaggcgagaaa", 2 };
    BOOST_REQUIRE_EQUAL(randWriter.freq("ga", 'g'), 4);
    BOOST_REQUIRE_EQUAL(randWriter.freq("ga", 'a'), 1);
    BOOST_REQUIRE_EQUAL(randWriter.freq("ga", 'c'), 0);
    BOOST_REQUIRE_EQUAL(randWriter.freq("ag", 'g'), 2);
    BOOST_REQUIRE_EQUAL(randWriter.freq("ag", 'a'), 3);
    BOOST_REQUIRE_EQUAL(randWriter.freq("aa", 'a'), 1);
    BOOST_REQUIRE_EQUAL(randWriter.freq("aa", 'g'), 1);
}

// Checks if `RandWriter::freq(const std::string&)` works correctly. It should return 0 if the
// provided k-gram is not presented in the text.
BOOST_AUTO_TEST_CASE(testFreq3) {
    const RandWriter randWriter{ "gagggagaggcgagaaa", 2 };
    BOOST_REQUIRE_EQUAL(randWriter.freq("cc"), 0);
    BOOST_REQUIRE_EQUAL(randWriter.freq("ac"), 0);
}

// Checks if `RandWriter::freq(const std::string&, char)` works correctly. It should return 0 if the
// provided k-gram is not presented in the text or the frequency of a character is 0.
BOOST_AUTO_TEST_CASE(testFreq4) {
    const RandWriter randWriter{ "gagggagaggcgagaaa", 2 };
    BOOST_REQUIRE_EQUAL(randWriter.freq("ga", 'c'), 0);
    BOOST_REQUIRE_EQUAL(randWriter.freq("cg", 'g'), 0);
    BOOST_REQUIRE_EQUAL(randWriter.freq("cc", 'c'), 0);
    BOOST_REQUIRE_EQUAL(randWriter.freq("ac", 'g'), 0);
}

// Checks if `RandWriter::freq(const std::string&)` throws an exception when the provided k-gram
BOOST_AUTO_TEST_CASE(testWrongKgram1) {
    const RandWriter randWriter{ "gagggagaggcgagaaa", 2 };
    BOOST_REQUIRE_THROW(std::cout << randWriter.freq("gag"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testWrongKgram2) {
    const RandWriter randWriter{ "gagggagaggcgagaaa", 2 };
    BOOST_REQUIRE_THROW(std::cout << randWriter.freq("gag"), std::invalid_argument);
}
