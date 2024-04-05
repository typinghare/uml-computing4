// Copyright 2024 James Chen

#include "RandWriter.hpp"
#include <iostream>
#include <random>

RandWriter::RandWriter(const std::string& text, const size_t k) : order_k_(k) {
    // Check if order k is greater than the length of the given text
    if (k > text.size()) {
        throw std::invalid_argument("The order k should be less then the size of the text!");
    }

    // Use slide window technique to scan all k-grams in the given text
    const auto circularText = text + text.substr(0, k);
    for (size_t i = 0; i < circularText.length() - k; ++i) {
        const auto kgram = circularText.substr(i, k);
        const auto nextChar = circularText.at(i + k);
        symbol_table_.increment(kgram, nextChar);
    }
}

size_t RandWriter::orderK() const { return order_k_; }

int RandWriter::freq(const std::string& kgram) const {
    checkKgram(kgram);
    return symbol_table_.frequencyOf(kgram);
}

int RandWriter::freq(const std::string& kgram, const char c) const {
    checkKgram(kgram);
    return symbol_table_.frequencyOf(kgram, c);
}

std::string RandWriter::generate(const std::string& kgram, const size_t L) {
    checkKgram(kgram);

    std::string generatedText = kgram;
    for (size_t i = 0; i < L - order_k_; ++i) {
        const auto& lastKgram = generatedText.substr(i, order_k_);
        const auto nextChar = kRand(lastKgram);
        generatedText.push_back(nextChar);
    }

    return generatedText;
}

// ReSharper disable once CppMemberFunctionMayBeConst
char RandWriter::kRand(const std::string& kgram) {
    const auto totalFrequency = symbol_table_.frequencyOf(kgram);
    const auto randomIndex = getRandomNumber(totalFrequency);
    const auto frequencyTable = symbol_table_.frequencyMapOf(kgram);

    int cumulative_frequency = 0;
    for (const auto& [c, frequency] : frequencyTable) {
        cumulative_frequency += frequency;
        if (cumulative_frequency >= randomIndex) {
            return c;
        }
    }

    return '\0';
}

std::ostream& operator<<(std::ostream& os, const RandWriter& randWriter) {
    static const std::string INDENT = "--- ";

    randWriter.symbol_table_.traverse(
        [&](auto kgram, auto totalFreq) { os << kgram << ": " << totalFreq << std::endl; },
        [&](auto c, auto freq) { os << INDENT << c << ": " << freq << std::endl; });

    return os;
}

void RandWriter::checkKgram(const std::string& kgram) const {
    if (kgram.length() != order_k_) {
        throw std::invalid_argument("Invliad k-gram: " + kgram);
    }
}

int RandWriter::getRandomNumber(const int totalFreq) {
    static std::random_device randomDevice;
    static std::mt19937 gen(randomDevice());

    if (totalFreq <= 0) {
        return 0;
    }

    std::uniform_int_distribution distribution(1, totalFreq);
    return distribution(gen);
}
