// Copyright 2022 Dr. Rykalova
// Editted by Dr. Daly
// test.cpp for PS1a
// updated 1/8/2024

#include <iostream>
#include <sstream>
#include <string>

#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

using PhotoMagic::FibLFSR;

BOOST_AUTO_TEST_CASE(testStepInstr) {
    FibLFSR l("1011011000110110");
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
}

BOOST_AUTO_TEST_CASE(testGenerateInstr) {
    FibLFSR l("1011011000110110");
    BOOST_REQUIRE_EQUAL(l.generate(9), 51);
}

// Test the output operator. The output string should be equal to the seed
// string if the LFSR object was not modified
BOOST_AUTO_TEST_CASE(testOutputOperator) {
    const std::string initialLFSR = "0110110001101100";
    const FibLFSR l(initialLFSR);
    std::stringstream ss;
    ss << l;
    BOOST_REQUIRE_EQUAL(ss.str(), initialLFSR);
}

// The the output operator. The output string should change after calling the
// generate method (k >= 1). The expected LFSR value is
BOOST_AUTO_TEST_CASE(testGenerateAndOutput) {
    const std::string initialLFSR = "0110110001101100";
    const std::string expectedLFSRAfterGenerate = "1101100001100110";
    FibLFSR l(initialLFSR);
    l.generate(9);

    std::stringstream ss;
    ss << l;
    BOOST_REQUIRE_EQUAL(ss.str(), expectedLFSRAfterGenerate);
}

// Test the lfsr
BOOST_AUTO_TEST_CASE(testLfsr) {
    FibLFSR l("0110110001101100");
    l.generate(9);

    BOOST_REQUIRE_EQUAL(l.getLfsr(), 55398);
}
