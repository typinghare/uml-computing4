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


#include "PhotoMagic.hpp"

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
// string if the LFSR object is not modified
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

// Test the PhotoMagic::convertPasswordToSeed() method
BOOST_AUTO_TEST_CASE(testConvertPasswordToSeed) {
    const std::string password = "fd79a712hdsa9";
    const std::string seed = PhotoMagic::convertPasswordToSeed(password);

    // Expect the length of the seed to be 16
    BOOST_REQUIRE_EQUAL(seed.length(), PhotoMagic::FibLFSR::SEED_LENGTH);

    // Expect all characters to be either '0' or '1'
    bool isAllBit = true;
    for (const char& c : seed) {
        if (c != '0' && c != '1') {
            isAllBit = false;
            break;
        }
    }
    BOOST_REQUIRE(isAllBit);
}

// An image should be completely the same as the original image after being
// transformed twice by the same seed.
BOOST_AUTO_TEST_CASE(testM) {
    static const auto SEED = "0000111100001111";

    sf::Image image;
    image.loadFromFile("img/cat.jpg");

    // Transform the image
    FibLFSR fibLfsr{ SEED };
    transform(image, &fibLfsr);

    // Tranform the image back using the same seed (restoring)
    fibLfsr = FibLFSR{ SEED };
    transform(image, &fibLfsr);

    const sf::Image originalImage;
    image.loadFromFile("img/cat.jpg");

    // Traverse all pixels and check if the restored image is completely equals
    // to the original image
    bool isTwoImagesSame = true;
    const sf::Vector2u size = originalImage.getSize();
    for (unsigned int row = 0; row < size.y; ++row) {
        for (unsigned int col = 0; col < size.x; ++col) {
            const sf::Color originalPixel = originalImage.getPixel(col, row);
            const sf::Color restoredPixel = image.getPixel(col, row);

            if (originalPixel.r != restoredPixel.r ||
                originalPixel.g != restoredPixel.g ||
                originalPixel.b != restoredPixel.b) {
                isTwoImagesSame = false;
                break;
            }
        }
    }
    BOOST_REQUIRE(isTwoImagesSame);
}
