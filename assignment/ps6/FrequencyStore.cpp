// Copyright 2024 James Chen

#include "FrequencyStore.hpp"

#include <iostream>
#include <utility>

FrequencyStore::FrequencyStore() : m_totalFrequency(0) {}

FrequencyStore::FrequencyStore(std::unordered_map<char, int> charMap) :
    m_charMap(std::move(charMap)), m_totalFrequency(0) {
    m_frequencyMap.resize(m_charMap.size(), 0);
}

int FrequencyStore::totalFrequency() const { return m_totalFrequency; }

void FrequencyStore::incrementFrequency(const char& c) {
    const auto it = m_charMap.find(c);
    if (it != m_charMap.end()) {
        m_frequencyMap[it->second] += 1;
        ++m_totalFrequency;
    }
}

int FrequencyStore::frequencyOf(const char& c) const {
    const auto it = m_charMap.find(c);
    return it == m_charMap.end() ? 0 : m_frequencyMap[it->second];
}

int FrequencyStore::frequencyAt(const int& index) const {
    return m_frequencyMap.at(index);
}
