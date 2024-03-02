// Copyright 2024 James Chen

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

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
    const Universe universe{ "assets/data/binary.txt" };
    const auto celestialBody = universe[1];
    constexpr float EXPECTED_POSITION_X = 0.0e00;
    constexpr float EXPECTED_POSITION_Y = -4.5e10;
    constexpr float EXPECTED_VELOCITY_X = -1.0e04;
    constexpr float EXPECTED_VELOCITY_Y = 0.0e00;
    constexpr double EXPECTED_MASS = 1.5e30;

    BOOST_REQUIRE_EQUAL(celestialBody.getPosition().x, EXPECTED_POSITION_X);
    BOOST_REQUIRE_EQUAL(celestialBody.getPosition().y, EXPECTED_POSITION_Y);
    BOOST_REQUIRE_EQUAL(celestialBody.getVelocity().x, EXPECTED_VELOCITY_X);
    BOOST_REQUIRE_EQUAL(celestialBody.getVelocity().y, EXPECTED_VELOCITY_Y);
    BOOST_REQUIRE_EQUAL(celestialBody.getMass(), EXPECTED_MASS);
}
