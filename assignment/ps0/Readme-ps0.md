# PS0: Hello SFML

## Contact

Name: Zhuojian Chen (James)

Section: COMP 2040 P 1 203

Time to Complete: Jan 19, 2024

## Description

This project creates a small game using SFML. Players can control a battle plane using `W` (Up), `A` (Left), `S` (Down), and `D` (Right). Note that this project uses `SFML v2.6`.

### Features

I wrote a game using pygame (in Python) last semester in an OOPL class. I am trying whether I can implement some similar functions using SFML.

### Issues

#### Build Problem

I cannot build my project using the `Makefile` provided by my professor. I am using macOS (ARM) and CMake. I installed SFML using HomeBrew and I specify the path of SFML in the `CMakeLists.txt` file. I can build and run my program successfully using CMake. However, when I try to build it using the `Makefile`, I keep getting some weird errors that I have no idea about.

I was totally at a loss and I asked ChatGPT about this, and it said that I should add the following to options to the command:

```bash
-I /opt/homebrew/include
-L /opt/homebrew/lib
```

According to ChatGPT, `-I` is a compiler flag used to add additional directories to the list of directories to be searched for header files, and `L` is a linker flag used to add additional directories to the list of directories to be searched for libraries during the linking phase of the build.

I added the two commands to the `Makefile`, and I can compile my files at the end. I deleted these two options when uploading the code to Gradescope.

#### Lint Problem

The cpplint keeps warning me about the indentation. It requires me to add a space before access modifiers such as `private` and `public`. But my IDE's formatter does not support this. So I ignore the problems.

~~~text
main.cpp:18:  public: should be indented +1 space inside class Direction  [whitespace/indent] [3]
main.cpp:49:  private: should be indented +1 space inside class Direction  [whitespace/indent] [3]
main.cpp:70:  public: should be indented +1 space inside class final  [whitespace/indent] [3]
main.cpp:76:  Lines should be <= 80 characters long  [whitespace/line_length] [2]
main.cpp:144:  private: should be indented +1 space inside class final  [whitespace/indent] [3]
~~~

### Extra Feature

In my code, I created a `ControllableSprite` that extends `sf::Sprite`. There are three public functions in the class: `enableDirection`, `disableDirection`, and `update`. Whenever the players press a direction key (WASD), it enables the corresponding direction; on the contrary, it disables the corresponding direction when players release a direction key. The `update` function will be invoked in each game frame, calculate the displacement of the sprite concerning the given delta time, and update its position.

I also encapsulate a useful utility class called `Direction` to simplify the logic and increase readability. Actually, the code I uploaded is the second version. The first version has been deleted because it is too verbose without a `Direction` class.

## Integrity

Read the University policy on Academic Integrity, and answer the following question:

There are six examples of academic misconduct, labeled (a) through (f). Other than (a), "Seeks to claim credit for the work or efforts of another without authorization or citation," which of these do you think would most apply to this class, and why? Write approx. 100-200 words. Note: there is no single correct answer to this. I am looking for your opinion.

I carefully read the Academic Integrity Statement on [UMass Lowell's official website](https://www.uml.edu/catalog/undergraduate/policies/academic-policies/academic-integrity.aspx#:~:text=Students%20are%20responsible%20for%20the,all%20programs%20of%20the%20university.). In the
**Academic Dishonesty and Misconduct Subject to Disciplinary Action
** sections, there are eight examples at the moment.

I think the **fifth item
** "Submission of academic work for which credit has already been earned without instructor permission (“self-plagiarism”)" and the
**seventh item** "Assists other students in any of these acts" would apply most to this class.

As everybody knows, code is an academic achievement that is most likely to be plagiarized. Some students use the same code for several classes to reduce their workload. However, they cannot learn anything new from the class if they do so. It is also immoral to give code to others and just let them copy and paste. But I am a bit confused when reading this. Is refactoring my previous code regarded as a self-plagiarism? I have written a lot of code and I often transplant some code from one language to another. I do this to learn a new language and review the language that I learned a couple of years ago. For the "ps0" homework, I reviewed the game I created in Python, and I transplanted some logic to this homework. I finish everything by myself without relying on AI. I added lots of comments to showcase my idea while writing code.

I often help others with their code, point out the problems they have, and address their issues. I don't directly share my code with others, but sometimes I give them a quick look. I am not sure if this act is considered to be against academic integrity. If it does, I will not do it again.

## Acknowledgments

I received help from ChatGPT on configuring the `CMakeLists.txt` file. I installed `SFML` using `HomeBrew` on my MacBook and added the following code to my `CMakeLists.txt`.

```cmake
set(SFML_DIR "/opt/homebrew/opt/sfml")
find_package(SFML 2.6 COMPONENTS graphics REQUIRED)
```

I use CLion Nova IDE, a JetBrains product, for my homework. I then copy and paste my code into Ubuntu running on a virtual machine. I opted for Parallels as the virtual machine software, since VirtualBox is incompatible with macOS ARM architecture. Going forward, all my homework will be completed using CLion Nova.

### Credits

A battle plane picture from the internet:

![battle plane](./sprite.png)
