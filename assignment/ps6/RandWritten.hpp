// Copyright 2024 James Chen

#ifndef RANDWRITTEN_H
#define RANDWRITTEN_H

#include <string>
#include <unordered_map>

/**
 * @brief A class for generating text using a Markov model. This class provides functionalities to
 * create and utilize a Markov model of order k from a given text, allowing the generation of new
 * text based on the learned patterns.
 */
class RandWriter {
 public:
    /**
     * @brief The size of the characters in the ASCII set.
     */
    static constexpr size_t ASCII_SIZE = 128;

    /**
     * @brief Constructs a RandWriter object with a Markov model of order k. Creates a Markov model
     * of order k from the provided text. The order k represents the number of preceding characters
     * considered for predicting the next character.
     * @param text The text used to create the Markov model.
     * @param k The order of the Markov model.
     */
    RandWriter(const std::string& text, size_t k);

    /**
     * @brief Returns the order of the Markov model.
     * @return The order of the Markov model.
     */
    [[nodiscard]] size_t orderK() const;

    /**
     * @brief Returns the number of occurrences of a specific k-gram in the text.
     * @param kgram The k-gram to search for.
     * @return The frequency of the k-gram in the text.
     * @throw std::invalid_argument If the length of kgram is not equal to the order of the Markov
     * model.
     */
    [[nodiscard]] int freq(const std::string& kgram) const;

    /**
     * @brief Returns the number of times a character follows a specific k-gram in the text.
     * @param kgram The k-gram preceding the character.
     * @param c The character to check for.
     * @return The frequency of character c following the k-gram.
     * @throw std::invalid_argument If the length of kgram is not equal to the order of the Markov
     * model.
     */
    [[nodiscard]] int freq(const std::string& kgram, char c) const;

    /**
     * @brief Generates a string of specified length using the Markov chain. Generates a string of
     * length L characters by simulating a trajectory through the Markov chain learned from the
     * input text. The initial k characters of the generated string are provided as the argument
     * kgram.
     * @param kgram The initial k characters of the generated string.
     * @param L The length of the generated string.
     * @return The generated string.
     * @throw std::invalid_argument If the length of kgram is not equal to the order of the Markov
     * model.
     */
    std::string generate(const std::string& kgram, size_t L);

 private:
    void checkKgram(const std::string& kgram) const;

    size_t m_orderK;

    std::unordered_map<std::string, std::array<int, ASCII_SIZE>> m_symbolTable;
};


#endif
