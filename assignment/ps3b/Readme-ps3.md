# PS3b: Sokoban

## Contact

Name: Zhuojian Chen (James)

Student ID: 02151380

Section: COMP 2040 P 1 203

Time to Complete: Feb 22, 2024

## Description

In this project, I created a small Sokoban game by leveraging SFML. In `ps3a`, I have just implemented the functionalities that read contents from a level file and initialize the UI.

### Features

* **Overrode the ">>" operator for the Sokoban class
  **: This allows users to read a level file to the game quickly and easily. The overriding takes `std::ifstream` and `Sokoban` as parameters. It first reads the height and width of the map from the first line of the file and sets the `height` and `width` properties in `Sokoban`. Then the program reads the characters based on the `height` and `width` and initializes the tile grid.
* **Tile Grid
  **:  A `vector` is used to represent the tile grid. The vector is one-dimensional, and the grid is mapped to which in row-major order. Note that tile includes floor, wall, boxes, and so on, but the player is not included.
* **Update frame by delta time
  **: An `update(dt)` method is created to update the game in each frame based on the delta time (the time between two frames). In `ps3a`, this is used to update the elapsed time in milliseconds.
* **Draw onto the window** I overrode the `draw` method in the`sf::Drawable` class, where the *tile
  grid*, *the player*, and *the elapsed time* (in the upper-left corner) are sequentially drawn.

### Memory

In `ps3a`, I created several pointers and containers (`unordered_map` and `vector`) that contain pointers. I used original pointers instead of smart pointers to understand better how to manage memory. I deleted all pointers and released all memory in the destructor of `Sokoban`.

In `ps3b`, I will use smart pointers to meet with the best practices in developing games in C++.

### Lambdas

I didn't use any lambdas and algorithm functions in `ps3a`, as I didn't have any scenarios where I needed to use algorithms and lambdas so far. I'll try to use this feature in `ps3b`.

### Extra Credit

I have printed the elapsed time in the upper left corner. The font file is downloaded from the internet and it is free. I have attached the link to the font file in the `Acknowledgments`.

## Acknowledgements

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban

Digital 7 Font: https://www.dafont.com/digital-7.font

### Reference

* [SFML - Text and fonts](https://www.sfml-dev.org/tutorials/2.6/graphics-text.php)
* [GCC Environment Variables](https://gcc.gnu.org/onlinedocs/cpp/Environment-Variables.html)
