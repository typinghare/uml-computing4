// Copyright 2024 James Chen

#ifndef INVALIDCOORDINATEEXCEPTION_H
#define INVALIDCOORDINATEEXCEPTION_H

#include <string>
#include <SFML/Graphics.hpp>

namespace SB {

/**
 * @brief This exception is thrown when an invalid coordinate is used.
 */
class InvalidCoordinateException final : public std::exception {
 public:
    /**
     * @brief Creates an InvalidCoordinateException instance.
     * \param coordinate The invalid coordinate.
     */
    explicit InvalidCoordinateException(const sf::Vector2i& coordinate) noexcept;

    /**
     * @brief Gets the excception message.
     */
    const char* what() const noexcept override;

 private:
    /**
     * @brief The exception message.
     */
    std::string message;
};

}  // namespace SB

#endif
