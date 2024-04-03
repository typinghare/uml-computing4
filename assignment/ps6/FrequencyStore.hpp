// Copyright 2024 James Chen

#ifndef FREQUENCYSTORAGE_H
#define FREQUENCYSTORAGE_H

#include <unordered_map>
#include <vector>

/**
 * @brief Represents a storage for frequencies of characters. It maintains a mapping of characters
 * to their frequencies using an external unordered_map<char, int>.
 */
class FrequencyStore {
 public:
    /**
     * @brief Default constructor.
     */
    FrequencyStore();

    /**
     * @brief Constructs a FrequencyStore object with the given character frequency mapping.
     * @param charMap The mapping of characters to their frequencies.
     */
    explicit FrequencyStore(std::unordered_map<char, int> charMap);

    /**
     * @brief Retrieves the total frequency of all characters in the store.
     * @return The total frequency.
     */
    [[nodiscard]] int totalFrequency() const;

    /**
     * @brief Increments the frequency of the given character. If the character exists in the
     * character map, its frequency is incremented in the frequency map.
     * @param c The character whose frequency needs to be incremented.
     */
    void incrementFrequency(const char& c);

    /**
     * @brief Retrieves the frequency of the given character. If the character exists in the
     * character map, returns its frequency from the frequency map;
     * otherwise, returns 0.
     * @param c The character whose frequency needs to be retrieved.
     * @return The frequency of the character.
     */
    [[nodiscard]] int frequencyOf(const char& c) const;

    /**
     * @brief Gets the frequency at the given index.
     * @param index The index of the frequency to be retrieved.
     * @return The frequency at the specified index
     */
    [[nodiscard]] int frequencyAt(const int& index) const;

 private:
    /**
     * @brief Reference to the external character frequency map.
     */
    std::unordered_map<char, int> m_charMap;

    /**
     * @brief Stores the frequency of characters.
     */
    std::vector<int> m_frequencyMap;

    /**
     * @brief Total frequency of all characters in the store.
     */
    int m_totalFrequency;
};


#endif
