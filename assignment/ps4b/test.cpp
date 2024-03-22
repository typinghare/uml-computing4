// Copyright 2024 James Chen

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "Universe.hpp"

/**
 * @brief Compares two values within tolerance.
 * @param x The first value to compare.
 * @param y The second value to compare.
 * @param tolerance The allowable percentage difference between x and y (default is 1%).
 * @return True if the absolute difference between x and y is within the specified tolerance, false
 * otherwise
 */
template <typename T>
bool equalWithinTolerance(T x, T y, double tolerance = 0.01) {
    return std::abs(x - y) <= tolerance * std::abs(y);
}

// Tests if `Universe::getNumPlanets()` and `Universe::getRadius` work correcly.
BOOST_AUTO_TEST_CASE(testUniverseBasic) {
    const NB::Universe universe{ "assets/1body.txt" };

    constexpr auto EXPECTED_NUM_PLANETS = 1;
    constexpr auto EXPECTED_RADIUS = 100.0;
    BOOST_REQUIRE_EQUAL(universe.numPlanets(), EXPECTED_NUM_PLANETS);
    BOOST_REQUIRE_EQUAL(universe.radius(), EXPECTED_RADIUS);
}

// Tests if `Universe::getNumPlanets()` and `Universe::getRadius` work correcly.
BOOST_AUTO_TEST_CASE(testUniverseBasic2) {
    const NB::Universe universe{ "assets/binary.txt" };

    constexpr auto EXPECTED_NUM_PLANETS = 2;
    constexpr auto EXPECTED_RADIUS = 5.0e10;
    BOOST_REQUIRE_EQUAL(universe.numPlanets(), EXPECTED_NUM_PLANETS);
    BOOST_REQUIRE_EQUAL(universe.radius(), EXPECTED_RADIUS);
}

// Tests if `CelestialBody::getNumPlanets()`, `CelestialBody::getRadius()` and
// `CelestialBody::getMass()` work correcly.
BOOST_AUTO_TEST_CASE(testCelestialBodyBasic) {
    const NB::Universe universe{ "assets/planets.txt" };
    const auto celestialBody = universe[0];

    constexpr float EXPECTED_POSITION_X = 1.4960e+11;
    constexpr float EXPECTED_POSITION_Y = 0.0000e+00;
    constexpr float EXPECTED_VELOCITY_X = 0.0000e+00;
    constexpr float EXPECTED_VELOCITY_Y = 2.9800e+04;
    constexpr float EXPECTED_MASS = 5.9740e+24;
    BOOST_REQUIRE_EQUAL(celestialBody.position().x, EXPECTED_POSITION_X);
    BOOST_REQUIRE_EQUAL(celestialBody.position().y, EXPECTED_POSITION_Y);
    BOOST_REQUIRE_EQUAL(celestialBody.velocity().x, EXPECTED_VELOCITY_X);
    BOOST_REQUIRE_EQUAL(celestialBody.velocity().y, EXPECTED_VELOCITY_Y);
    BOOST_REQUIRE(equalWithinTolerance(celestialBody.mass(), EXPECTED_MASS));
}

// Tests if `Universe::operator[]` works for the non-first elements.
BOOST_AUTO_TEST_CASE(testUniverseBracketOperator1) {
    const NB::Universe universe{ "assets/3body.txt" };
    const auto celestialBody = universe[1];

    constexpr float EXPECTED_POSITION_X = 0.0;
    constexpr float EXPECTED_POSITION_Y = 4.50e10;
    constexpr float EXPECTED_VELOCITY_X = 3.00e04;
    constexpr float EXPECTED_VELOCITY_Y = 0.0e00;
    constexpr float EXPECTED_MASS = 1.989e30;
    BOOST_REQUIRE_EQUAL(celestialBody.position().x, EXPECTED_POSITION_X);
    BOOST_REQUIRE_EQUAL(celestialBody.position().y, EXPECTED_POSITION_Y);
    BOOST_REQUIRE_EQUAL(celestialBody.velocity().x, EXPECTED_VELOCITY_X);
    BOOST_REQUIRE_EQUAL(celestialBody.velocity().y, EXPECTED_VELOCITY_Y);
    BOOST_REQUIRE(equalWithinTolerance(celestialBody.mass(), EXPECTED_MASS));
}

// Tests if `Universe::operator[]` works for the last elements.
BOOST_AUTO_TEST_CASE(testUniverseBracketOperator2) {
    const NB::Universe universe{ "assets/uniform8.txt" };
    const auto celestialBody = universe[universe.numPlanets() - 1];

    constexpr float EXPECTED_POSITION_X = 3.535534e+08;
    constexpr float EXPECTED_POSITION_Y = -3.535534e+08;
    constexpr float EXPECTED_VELOCITY_X = -1.934345e+02;
    constexpr float EXPECTED_VELOCITY_Y = -1.934345e+02;
    constexpr float EXPECTED_MASS = 2.00e+23;
    BOOST_REQUIRE_EQUAL(celestialBody.position().x, EXPECTED_POSITION_X);
    BOOST_REQUIRE_EQUAL(celestialBody.position().y, EXPECTED_POSITION_Y);
    BOOST_REQUIRE_EQUAL(celestialBody.velocity().x, EXPECTED_VELOCITY_X);
    BOOST_REQUIRE_EQUAL(celestialBody.velocity().y, EXPECTED_VELOCITY_Y);
    BOOST_REQUIRE(equalWithinTolerance(celestialBody.mass(), EXPECTED_MASS));
}

// Tests if `Universe::operator[]` works for the last elements.
BOOST_AUTO_TEST_CASE(testUniverseBracketOperator3) {
    const NB::Universe universe{ "assets/8star-rotation.txt" };
    const auto celestialBody = universe[universe.numPlanets() - 1];

    constexpr float EXPECTED_POSITION_X = -13.125e10;
    constexpr float EXPECTED_POSITION_Y = 0;
    constexpr float EXPECTED_VELOCITY_X = 0;
    constexpr float EXPECTED_VELOCITY_Y = 81e3;
    constexpr float EXPECTED_MASS = 5e29;
    BOOST_REQUIRE_EQUAL(celestialBody.position().x, EXPECTED_POSITION_X);
    BOOST_REQUIRE_EQUAL(celestialBody.position().y, EXPECTED_POSITION_Y);
    BOOST_REQUIRE_EQUAL(celestialBody.velocity().x, EXPECTED_VELOCITY_X);
    BOOST_REQUIRE_EQUAL(celestialBody.velocity().y, EXPECTED_VELOCITY_Y);
    BOOST_REQUIRE(equalWithinTolerance(celestialBody.mass(), EXPECTED_MASS));
}

// Tests if "CelestialBody::operator>>" and "CelestialBody::operator<<" works correctly.
BOOST_AUTO_TEST_CASE(testCelestialBodyOutput) {
    std::ifstream fileStream{ "assets/uniform8.txt" };
    std::string line;
    getline(fileStream, line);
    getline(fileStream, line);
    getline(fileStream, line);
    getline(fileStream, line);

    const std::string EXPECT_LINE =
        " 3.535534e+08  3.535534e+08  1.934345e+02 -1.934345e+02 2.00e+23 earth.gif";

    BOOST_REQUIRE_EQUAL(line, EXPECT_LINE);
}

// Tests if "Universe::operator>>" and "Universe::operator<<" works correctly.
BOOST_AUTO_TEST_CASE(testIdentifyBrokenImplementation) {
    const NB::Universe universe{ "assets/3body.txt" };
    std::stringstream stringstream;
    stringstream << universe;

    const std::string EXPECT_STRING = "3\n1.25e11\n"
                                      "0.00e00  0.00e00  0.05e04  0.00e00  5.974e24  earth.gif\n"
                                      "0.00e00  4.50e10  3.00e04  0.00e00  1.989e30  sun.gif\n"
                                      "0.00e00 -4.50e10 -3.00e04  0.00e00  1.989e30  sun.gif";

    BOOST_REQUIRE_EQUAL(stringstream.str(), EXPECT_STRING);
}

// Tests if `Universe::step()` works correctly
BOOST_AUTO_TEST_CASE(testUniverseStep1) {
    NB::Universe universe{ "assets/planets.txt" };
    constexpr double DELTA_TIME = 25000.0;
    universe.step(DELTA_TIME);

    const auto celestialBody = universe[0];
    BOOST_CHECK_MESSAGE(
        equalWithinTolerance(celestialBody.position().x, 1.495e11F),
        "x is not within 1% tolerance.");
    BOOST_CHECK_MESSAGE(
        equalWithinTolerance(celestialBody.position().y, 7.45e8F), "y is not within 1% tolerance.");
    BOOST_CHECK_MESSAGE(
        equalWithinTolerance(celestialBody.velocity().x, -148.201F),
        "vx is not within 1% tolerance.");
    BOOST_CHECK_MESSAGE(
        equalWithinTolerance(celestialBody.velocity().y, 29800.F),
        "vy is not within 1% tolerance.");
}
