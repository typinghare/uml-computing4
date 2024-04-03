// Copyright 2024 James Chen

#include "RandWriter.hpp"
#include <array>
#include <random>
#include <stdexcept>

RandWriter::RandWriter(const std::string& text, const size_t k) : m_orderK(k) {
    // Initialize charMap
    for (const auto& c : text) {
        const auto it = m_charMap.find(c);
        if (it == m_charMap.end()) {
            m_charMap[c] = static_cast<int>(m_charMap.size());
        }
    }

    const auto circularText = text + text.substr(0, k);
    for (size_t i = 0; i < circularText.length() - k; ++i) {
        const auto kgram = circularText.substr(i, k);
        const auto nextChar = circularText.at(i + k);
        const auto symbolEntry = m_symbolTable.find(kgram);
        if (symbolEntry == m_symbolTable.end()) {
            // Create new frequency
            const FrequencyStore frequencyStore{ m_charMap };
            m_symbolTable[kgram] = frequencyStore;
        }
        auto& frequencyStore = m_symbolTable[kgram];
        frequencyStore.incrementFrequency(nextChar);
    }
}

size_t RandWriter::orderK() const { return m_orderK; }

int RandWriter::freq(const std::string& kgram) const {
    checkKgram(kgram);

    const auto it = m_symbolTable.find(kgram);
    return it == m_symbolTable.end() ? 0 : it->second.totalFrequency();
}

int RandWriter::freq(const std::string& kgram, const char c) const {
    checkKgram(kgram);

    const auto it = m_symbolTable.find(kgram);
    return it == m_symbolTable.end() ? 0 : it->second.frequencyOf(c);
}

std::string RandWriter::generate(const std::string& kgram, const size_t L) const {
    checkKgram(kgram);

    std::string generatedText = kgram;
    for (size_t i = 0; i < L - m_orderK; ++i) {
        const auto& lastKgram = generatedText.substr(i, m_orderK);
        const auto nextChar = kRand(lastKgram);
        generatedText.push_back(nextChar);
    }

    return generatedText;
}

void RandWriter::checkKgram(const std::string& kgram) const {
    if (kgram.length() != m_orderK) {
        throw std::invalid_argument("Invliad k-gram: " + kgram);
    }
}

char RandWriter::kRand(const std::string& kgram) const {
    const auto& frequencyStore = m_symbolTable.at(kgram);
    const auto totalFreq = frequencyStore.totalFrequency();
    const auto randomIndex = getRandomNumber(totalFreq);

    int cumulativeFreq = 0;
    for (const auto& [c, index] : m_charMap) {
        cumulativeFreq += frequencyStore.frequencyAt(index);
        if (cumulativeFreq >= randomIndex) {
            return c;
        }
    }

    return '\0';
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
