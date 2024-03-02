// Copyright 2024 James Chen

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <sstream>
#include <boost/test/unit_test.hpp>
#include "Universe.hpp"

// Tests if `Universe::getNumPlanets()` and `Universe::getRadius` work correcly.
BOOST_AUTO_TEST_CASE(testUniverseBasic) {
    const Universe universe{ "assets/data/1body.txt" };

    constexpr auto EXPECTED_NUM_PLANETS = 1;
    constexpr auto EXPECTED_RADIUS = 100.0;
    BOOST_REQUIRE_EQUAL(universe.getNumPlanets(), EXPECTED_NUM_PLANETS);
    BOOST_REQUIRE_EQUAL(universe.getRadius(), EXPECTED_RADIUS);
}

// Tests if `Universe::getNumPlanets()` and `Universe::getRadius` work correcly.
BOOST_AUTO_TEST_CASE(testUniverseBasic2) {
    const Universe universe{ "assets/data/binary.txt" };

    constexpr auto EXPECTED_NUM_PLANETS = 2;
    constexpr auto EXPECTED_RADIUS = 5.0e10;
    BOOST_REQUIRE_EQUAL(universe.getNumPlanets(), EXPECTED_NUM_PLANETS);
    BOOST_REQUIRE_EQUAL(universe.getRadius(), EXPECTED_RADIUS);
}

// Tests if `CelestialBody::getNumPlanets()`, `CelestialBody::getRadius()` and
// `CelestialBody::getMass()` work correcly.
BOOST_AUTO_TEST_CASE(testCelestialBodyBasic) {
    const Universe universe{ "assets/data/1body.txt" };
    const auto celestialBody = universe[0];

    constexpr float EXPECTED_POSITION_X = 10.0;
    constexpr float EXPECTED_POSITION_Y = 20.0;
    constexpr float EXPECTED_VELOCITY_X = 2.0;
    constexpr float EXPECTED_VELOCITY_Y = 1.0;
    constexpr double EXPECTED_MASS = 1E20;
    BOOST_REQUIRE_EQUAL(celestialBody.getPosition().x, EXPECTED_POSITION_X);
    BOOST_REQUIRE_EQUAL(celestialBody.getPosition().y, EXPECTED_POSITION_Y);
    BOOST_REQUIRE_EQUAL(celestialBody.getVelocity().x, EXPECTED_VELOCITY_X);
    BOOST_REQUIRE_EQUAL(celestialBody.getVelocity().y, EXPECTED_VELOCITY_Y);
    BOOST_REQUIRE_EQUAL(celestialBody.getMass(), EXPECTED_MASS);
}

// Tests if `Universe::operator[]` works for the non-first elements.
BOOST_AUTO_TEST_CASE(testUniverseBracketOperator) {
    const Universe universe{ "assets/data/3body.txt" };
    const auto celestialBody1 = universe[1];
    const auto celestialBody2 = universe[2];

    constexpr float EXPECTED_POSITION_X_1 = 0.0;
    constexpr float EXPECTED_POSITION_Y_1 = 4.50e10;
    constexpr float EXPECTED_VELOCITY_X_1 = 3.00e04;
    constexpr float EXPECTED_VELOCITY_Y_1 = 0.0e00;
    constexpr double EXPECTED_MASS_1 = 1.989e30;
    BOOST_REQUIRE_EQUAL(celestialBody1.getPosition().x, EXPECTED_POSITION_X_1);
    BOOST_REQUIRE_EQUAL(celestialBody1.getPosition().y, EXPECTED_POSITION_Y_1);
    BOOST_REQUIRE_EQUAL(celestialBody1.getVelocity().x, EXPECTED_VELOCITY_X_1);
    BOOST_REQUIRE_EQUAL(celestialBody1.getVelocity().y, EXPECTED_VELOCITY_Y_1);
    BOOST_REQUIRE_EQUAL(celestialBody1.getMass(), EXPECTED_MASS_1);

    constexpr float EXPECTED_POSITION_X_2 = 0.0;
    constexpr float EXPECTED_POSITION_Y_2 = -4.50e10;
    constexpr float EXPECTED_VELOCITY_X_2 = -3.00e04;
    constexpr float EXPECTED_VELOCITY_Y_2 = 0.0e00;
    constexpr double EXPECTED_MASS_2 = 1.989e30;
    BOOST_REQUIRE_EQUAL(celestialBody2.getPosition().x, EXPECTED_POSITION_X_2);
    BOOST_REQUIRE_EQUAL(celestialBody2.getPosition().y, EXPECTED_POSITION_Y_2);
    BOOST_REQUIRE_EQUAL(celestialBody2.getVelocity().x, EXPECTED_VELOCITY_X_2);
    BOOST_REQUIRE_EQUAL(celestialBody2.getVelocity().y, EXPECTED_VELOCITY_Y_2);
    BOOST_REQUIRE_EQUAL(celestialBody2.getMass(), EXPECTED_MASS_2);
}

// Tests if "CelestialBody::operator<<" works correctly.
BOOST_AUTO_TEST_CASE(testCelestialBodyOutput) {
    const Universe universe{ "assets/data/3body.txt" };
    const auto celestialBody1 = universe[1];
    const auto celestialBody2 = universe[2];

    std::stringstream stream;
    stream << celestialBody1;
    BOOST_REQUIRE_EQUAL(stream.str(), "0.00e+00 4.50e+10 3.00e+04 0.00e+00 1.99e+30 sun.gif");

    stream.str("");
    stream << celestialBody2;
    BOOST_REQUIRE_EQUAL(stream.str(), "0.00e+00 -4.50e+10 -3.00e+04 0.00e+00 1.99e+30 sun.gif");
}

// Tests if "Universe::operator<<" works correctly.
BOOST_AUTO_TEST_CASE(testUniverseOutput) {
    const Universe universe{ "assets/data/3body.txt" };

    std::stringstream stream;
    stream << universe;
    BOOST_REQUIRE_EQUAL(
        stream.str(), "3\n1.25e+11\n0.00e+00 0.00e+00 5.00e+02 0.00e+00 5.97e+24 earth.gif\n"
                      "0.00e+00 4.50e+10 3.00e+04 0.00e+00 1.99e+30 sun.gif\n"
                      "0.00e+00 -4.50e+10 -3.00e+04 0.00e+00 1.99e+30 sun.gif\n");
}
