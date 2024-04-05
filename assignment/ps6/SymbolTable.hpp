// Copyright 2024 James Chen

#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <functional>
#include <unordered_map>

using std::unordered_map;

/**
 * @brief SymbolTable class template for managing symbol frequencies.
 * @tparam S The type of symbols.
 * @tparam T The type of tokens.
 */
template <typename S, typename T>
class SymbolTable {
 public:
    /**
     * @brief Increments the frequency count for a symbol-next_token pair.
     * @param symbol The symbol to increment the frequency for.
     * @param next_token The token associated with the symbol.
     */
    void increment(S symbol, T next_token);

    /**
     * @brief Retrieves the total frequency count of a given symbol.
     * @param symbol The symbol to retrieve the frequency count for.
     * @return The total frequency count of the given symbol.
     */
    [[nodiscard]] int frequencyOf(S symbol) const;

    /**
     * @brief Retrieves the frequency count of a specific symbol-next_token pair.
     * @param symbol The symbol to retrieve the frequency count for.
     * @param next_token The symbol to retrieve the frequency count for.
     * @return The frequency count of the given symbol-next_token pair.
     */
    [[nodiscard]] int frequencyOf(S symbol, T next_token) const;

    /**
     * @brief Gets the frequency map of symbols.
     * @return The frequency map of symbols.
     */
    unordered_map<S, int> frequencyMap() const;

    /**
     * @brief Gets the frequency map of tokens associated with a specific symbol.
     * @param symbol The symbol to retrieve the frequency map for.
     * @return The frequency map of tokens associated with the given symbol.
     */
    unordered_map<T, int> frequencyMapOf(S symbol) const;

    /**
     * Traverses through the symbol table, invoking provided callbacks for symbol and token
     * information.
     * @param symbolCallback A callback function accepting a symbol and its total frequency;
     * @param tokenCallback A callback function accepting a token and its frequency;
     */
    void traverse(
        std::function<void(S, int)> symbolCallback,
        std::function<void(T, int)> tokenCallback) const;

 private:
    /**
     * @brief Map to store symbols and their corresponding frequency maps.
     */
    unordered_map<S, unordered_map<T, int>> frequency_table_;

    /**
     * @brief Map to store the total frequency of each token.
     */
    unordered_map<S, int> frequency_map_;
};

template <typename S, typename T>
void SymbolTable<S, T>::increment(S symbol, T next_token) {
    // Increment frequency for the symbol-next_token pair
    ++frequency_table_[symbol][next_token];

    // Increment total frequency for the symbol
    ++frequency_map_[symbol];
}

template <typename S, typename T>
int SymbolTable<S, T>::frequencyOf(S symbol) const {
    const auto entry = frequency_map_.find(symbol);
    return entry == frequency_map_.end() ? 0 : entry->second;
}

template <typename S, typename T>
int SymbolTable<S, T>::frequencyOf(S symbol, T next_token) const {
    // Return 0 if the given symbol does not exist
    const auto entry = frequency_table_.find(symbol);
    if (entry == frequency_table_.end()) {
        return 0;
    }

    const auto frequencyMap = entry->second;
    const auto frequencyEntry = frequencyMap.find(next_token);
    return frequencyEntry == frequencyMap.end() ? 0 : frequencyEntry->second;
}

template <typename S, typename T>
unordered_map<S, int, std::hash<S>, std::equal_to<S>> SymbolTable<S, T>::frequencyMap() const {
    return frequency_map_;
}

template <typename S, typename T>
unordered_map<T, int, std::hash<T>, std::equal_to<T>>
SymbolTable<S, T>::frequencyMapOf(S symbol) const {
    return frequency_table_.at(symbol);
}

template <typename S, typename T>
void SymbolTable<S, T>::traverse(
    std::function<void(S, int)> symbolCallback, std::function<void(T, int)> tokenCallback) const {
    for (auto const& [symbol, totalFrequency] : frequency_map_) {
        symbolCallback(symbol, totalFrequency);
        for (auto const& [token, frequency] : frequencyMapOf(symbol)) {
            tokenCallback(token, frequency);
        }
    }
}

#endif
