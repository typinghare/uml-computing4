# PS0: Hello SFML

## Contact

Name: Zhuojian Chen (James)

Section: COMP 2040 P 1 203

Time to Complete: Jan 19, 2024

## Description

This project creates a small game using SFML. Player can control a battle plane using `W` (Up), `A` (Left), `S` (Down), `D` (Right).

### Features

I wrote a game using pygame (in Python) last semester in a OOPL class. I am trying whether I can implement some 

### Issues

### Extra Feature

Describe anything special you did. This is required to earn points.

## Integrity

Read the University policy Academic Integrity, and answer the following question:

There are six examples of academic misconduct, labeled (a) through (f). Other than (a), "Seeks to claim credit for the work or efforts of another without authorization or citation," which of these do you think would most apply to this class, and why? Write approx. 100-200 words. Note: there is no single correct answer to this. I am looking for your opinion.

## Acknowledgements

I received help from ChatGPT on writing the `CMakeLists.txt` file. I installed `SFML` using `HomeBrew` on my MacBook, and added the following code to my `CMakeLists.txt`.

```cmake
set(SFML_DIR "/opt/homebrew/opt/sfml")
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
```

I use CLion Nova IDE, a JetBrains product, for my homework. I then copy and paste my code into Ubuntu running on a virtual machine. I opted for Parallels as the virtual machine software, since VirtualBox is incompatible with macOS ARM architecture. Going forward, all my homework will be completed using CLion Nova.

### Credits

List where you got any images or other resources.
