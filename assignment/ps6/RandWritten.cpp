// Copyright 2024 James Chen

#include "RandWritten.hpp"
#include <array>

RandWriter::RandWriter(const std::string& text, const size_t k) : m_orderK(k) {}

size_t RandWriter::orderK() const { return m_orderK; }

int RandWriter::freq(const std::string& kgram) const {
    checkKgram(kgram);
    return m_symbolTable.at(kgram).at(0);
}

int RandWriter::freq(const std::string& kgram, const char c) const {
    checkKgram(kgram);
    const auto array = m_symbolTable.at(kgram);

    return array.at(static_cast<size_t>(c));
}

std::string RandWriter::generate(const std::string& kgram, size_t L) {}

void RandWriter::checkKgram(const std::string& kgram) const {
    if (kgram.length() != m_orderK) {
        throw std::invalid_argument("Invliad k-gram: " + kgram);
    }
}
