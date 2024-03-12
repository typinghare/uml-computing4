// Copyright 2024 James Chen

#ifndef NBODYCONSTANT_HPP
#define NBODYCONSTANT_HPP

#include <filesystem>
#include <string>

namespace NB {

// Window title
constexpr std::string_view WINDOW_TITLE = "N-Body Problem Simulation by James Chen";

// Window has a fixed height/width; the window is a square
constexpr unsigned WINDOW_WIDTH = 720;
constexpr unsigned WINDOW_HEIGHT = WINDOW_WIDTH;

// Assets directory and subdirectories
const std::filesystem::path ASSETS_DIR = "assets";
const std::filesystem::path ASSETS_IMAGE_DIR = ASSETS_DIR;
const std::filesystem::path ASSETS_SOUND_DIR = ASSETS_DIR;

// Images
const std::filesystem::path IMAGE_BACKGRROUND = ASSETS_IMAGE_DIR / "background.jpg";

// Sounds
const std::filesystem::path SOUND_BACKGROUND_MUSIC = ASSETS_SOUND_DIR / "2001.wav";

// Double constants
constexpr double DOUBLE_HALF = 0.5;
constexpr double SCALE_FACTOR = 1.1;

}  // namespace NB

#endif
