// Copyright 2024 James Chen

// Checks if `EDistance::penalty` works correctly.

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <fstream>
#include <sstream>
#include <string>
#include <boost/test/unit_test.hpp>
#include "RandWriter.hpp"

/**
 * Reads content from a file.
 * @param filename The path of the file to read.
 * @return All the content of the file.
 */
std::string readFileContent(const std::string& filename) {
    std::ifstream ifstream(filename);
    std::ostringstream contentStream;
    std::string line;
    while (std::getline(ifstream, line)) {
        contentStream << line;
    }

    ifstream.close();

    return contentStream.str();
}

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

BOOST_AUTO_TEST_CASE(testOrderKFail) {
    BOOST_REQUIRE_THROW(const RandWriter randWriter("abc", 4), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testKRand1) {
    RandWriter randWriter{ "gagggagaggcgagaaa", 2 };
    for (int i = 0; i < 2 << 3; ++i) {
        BOOST_REQUIRE_EQUAL(randWriter.kRand("gc"), 'g');
    }
}

BOOST_AUTO_TEST_CASE(testKRand2) {
    RandWriter randWriter{ "gagggagaggcgagaaa", 3 };
    for (int i = 0; i < 2 << 3; ++i) {
        const auto nextChar = randWriter.kRand("gag");
        BOOST_REQUIRE(nextChar == 'g' || nextChar == 'a');
    }
}

// Checks if `RandWriter::generate()` works correctly: (1) The length of the generated text should
// be equal to the given length, and (2) the first k characters should be equal to the first k-gram.
BOOST_AUTO_TEST_CASE(testGenerate1) {
    constexpr int ORDER_K = 1;
    constexpr size_t LENGTH = 100;

    const std::string content = readFileContent("assets/romeo.txt");
    RandWriter randWriter{ content, ORDER_K };
    const auto firstKGram = content.substr(0, ORDER_K);
    const auto generatedText = randWriter.generate(firstKGram, LENGTH);
    BOOST_REQUIRE_EQUAL(generatedText.size(), LENGTH);
    BOOST_REQUIRE_EQUAL(generatedText.substr(0, ORDER_K), firstKGram);
}

// Checks if `RandWriter::generate()` works correctly: (1) The length of the generated text should
// be equal to the given length, and (2) the first k characters should be equal to the first k-gram.
BOOST_AUTO_TEST_CASE(testGenerate2) {
    constexpr int ORDER_K = 3;
    constexpr size_t LENGTH = 300;

    const std::string content = readFileContent("assets/tomsawyer.txt");
    RandWriter randWriter{ content, ORDER_K };
    const auto firstKGram = content.substr(0, ORDER_K);
    const auto generatedText = randWriter.generate(firstKGram, LENGTH);
    BOOST_REQUIRE_EQUAL(generatedText.size(), LENGTH);
    BOOST_REQUIRE_EQUAL(generatedText.substr(0, ORDER_K), firstKGram);
}

// Checks if `RandWriter::kRand()` follows a correct distribution.
BOOST_AUTO_TEST_CASE(testKRandDistribution) {
    constexpr int NUMBER_OF_TIMES = 1000;
    constexpr double PROBABILITY_OF_G = 0.8;
    constexpr float TOLERANCE = 10.F;

    RandWriter randWriter{ "gagggagaggcgagaaa", 2 };
    int numberOfG = 0;
    for (int i = 0; i < NUMBER_OF_TIMES; ++i) {
        const auto nextChar = randWriter.kRand("ga");
        if (nextChar == 'g') {
            ++numberOfG;
        }
    }

    const auto actualProbabilityOfG = static_cast<double>(numberOfG) / NUMBER_OF_TIMES;
    BOOST_REQUIRE_CLOSE(actualProbabilityOfG, PROBABILITY_OF_G, TOLERANCE);
}
