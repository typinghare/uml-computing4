# C++ Compiler
COMPILER = g++

# C++ Flags
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g -I /opt/homebrew/include
# CFLAGS = --std=c++17 -Wall -Werror -pedantic -g

# Libraries
LIB = -L /opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system
# LIB = -lsfml-graphics -lsfml-window -lsfml-system

# Code source directory
SRC = ./

# Hpp files (dependencies)
DEPS = ${SRC}Sokoban.hpp

# Object files
OBJECTS = ${SRC}main.o

# The object files that the static library includes
STATIC_LIB_OBJECTS = ${SRC}Sokoban.o

# Static library
STATIC_LIB = Sokoban.a

# Program
PROGRAM = Sokoban

.PHONY: all clean lint run

${SRC}%.o: ${SRC}%.cpp $(DEPS)
	$(COMPILER) $(CFLAGS) -c $<

$(PROGRAM): $(OBJECTS) $(STATIC_LIB)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

$(STATIC_LIB): $(STATIC_LIB_OBJECTS)
	ar rcs $@ $^

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM) assets/level/level1.lvl && make clean

clean:
	rm -f ${SRC}*.o $(PROGRAM) $(STATIC_LIB)

lint:
	cpplint *.hpp *.cpp