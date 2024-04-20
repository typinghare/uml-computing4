// Copyright 2024 James Chen

#include "WordWriter.hpp"
#include <iostream>
#include <random>
#include <sstream>

std::string to_string(const std::vector<std::string>& stringVector) {
    std::ostringstream stringStream;
    const auto maxIndex = stringVector.size() - 1;
    for (int i = 0; i <= maxIndex; ++i) {
        stringStream << stringVector.at(i);
        if (i != maxIndex) {
            stringStream << ' ';
        }
    }

    return stringStream.str();
}

WordWriter::WordWriter(const std::string& text, const size_t k) : order_k_(k) {
    // Check if order k is greater than the length of the given text
    if (k > text.size()) {
        throw std::invalid_argument("The order k should be less then the size of the text!");
    }

    // Split the text into tokens
    std::istringstream ss(text);
    std::string token;
    std::vector<std::string> token_vector;
    while (std::getline(ss, token, ' ')) {
        token_vector.push_back(token);
    }

    for (int i = 0; i < k; ++i) {
        token_vector.push_back(token_vector.at(i));
    }

    // Use slide window technique to scan all k-grams in the given text
    for (size_t i = 0; i < token_vector.size() - k; ++i) {
        std::vector<std::string> kgram;
        for (size_t j = 0; j < k; ++j) {
            kgram.push_back(token_vector.at(i + j));
        }
        const auto nextToken = token_vector.at(i + k);
        symbol_table_.increment(to_string(kgram), nextToken);
    }
}

std::string WordWriter::generate(const std::vector<std::string>& kgram, const size_t L) const {
    std::vector<std::string> generatedTextVector = kgram;
    for (size_t i = 0; i < L - order_k_; ++i) {
        std::vector<std::string> lastKGram;
        for (size_t j = 0; j < order_k_; ++j) {
            lastKGram.push_back(generatedTextVector.at(i + j));
        }
        const auto nextToken = kRand(lastKGram);
        generatedTextVector.push_back(nextToken);
    }

    std::ostringstream generatedTextStream;
    for (const auto& token : generatedTextVector) {
        generatedTextStream << token << ' ';
    }

    return generatedTextStream.str();
}

std::string WordWriter::kRand(const std::vector<std::string>& kgram) const {
    const auto kgramString = to_string(kgram);
    const auto totalFrequency = symbol_table_.frequencyOf(kgramString);
    const auto randomIndex = getRandomNumber(totalFrequency);
    const auto frequencyTable = symbol_table_.frequencyMapOf(kgramString);

    int cumulative_frequency = 0;
    for (const auto& [token, frequency] : frequencyTable) {
        cumulative_frequency += frequency;
        if (cumulative_frequency >= randomIndex) {
            return token;
        }
    }

    return "";
}

int WordWriter::getRandomNumber(const int totalFreq) {
    static std::random_device randomDevice;
    static std::mt19937 gen(randomDevice());

    if (totalFreq <= 0) {
        return 0;
    }

    std::uniform_int_distribution distribution(1, totalFreq);
    return distribution(gen);
}

std::ostream& operator<<(std::ostream& os, const WordWriter& wordWriter) {
    static const std::string INDENT = "--- ";

    wordWriter.symbol_table_.traverse(
        [&](auto kgram, auto totalFreq) { os << kgram << ": " << totalFreq << std::endl; },
        [&](auto word, auto freq) { os << INDENT << word << ": " << freq << std::endl; });

    return os;
}
