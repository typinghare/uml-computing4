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

BOOST_AUTO_TEST_CASE(testOutputOperator) {
    const std::string initialLFSR = "0110110001101100";
    const FibLFSR l(initialLFSR);
    std::stringstream ss;
    ss << l;
    BOOST_REQUIRE_EQUAL(ss.str(), initialLFSR);
}

BOOST_AUTO_TEST_CASE(testGenerateAndOutput) {
    const std::string initialLFSR = "0110110001101100";
    const std::string expectedLFSRAfterGenerate = "1101100001100110";
    FibLFSR l(initialLFSR);
    l.generate(9);

    std::stringstream ss;
    ss << l;
    BOOST_REQUIRE_EQUAL(ss.str(), expectedLFSRAfterGenerate);
}
