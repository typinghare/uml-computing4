# C++ Compiler
COMPILER = g++

# C++ Flags
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g

# Libraries
LIB = -lsfml-graphics -lsfml-window -lsfml-system -lboost_unit_test_framework

# Code source directory
SRC = ./

# Hpp files (dependencies)
DEPS = $(SRC)Sokoban.hpp \
       $(SRC)SokobanConstants.hpp \
       $(SRC)SokobanTileGrid.hpp \
       $(SRC)SokobanPlayer.hpp \
       $(SRC)SokobanScore.hpp \
       $(SRC)SokobanElapsedTime.hpp \
       $(SRC)InvalidCoordinateException.hpp \

# Object files that are not in the static library
OBJECTS = $(SRC)main.o

# The object files that the static library includes
STATIC_LIB_OBJECTS = $(SRC)Sokoban.o \
					 $(SRC)SokobanTileGrid.o \
					 $(SRC)SokobanPlayer.o \
					 $(SRC)SokobanScore.o \
 					 $(SRC)SokobanElapsedTime.o \
 					 $(SRC)InvalidCoordinateException.o \

# Static library
STATIC_LIB = Sokoban.a

# Program
PROGRAM = Sokoban

# The test object files
TEST_OBJECTS = $(SRC)test.o

# The test program
TEST_PROGRAM = test

.PHONY: all test clean lint run

$(SRC)%.o: $(SRC)%.cpp $(DEPS)
	$(COMPILER) $(CFLAGS) -c $<

$(PROGRAM): $(OBJECTS) $(STATIC_LIB)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

$(STATIC_LIB): $(STATIC_LIB_OBJECTS)
	ar rcs $@ $^

all: $(PROGRAM)

$(TEST_PROGRAM): $(TEST_OBJECTS) $(STATIC_LIB)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

# Run unit test
boost: $(TEST_PROGRAM)
	./$< && make clean

run: $(PROGRAM)
	./$< assets/level/level2.lvl && make clean

clean:
	rm -f $(SRC)*.o $(PROGRAM) $(STATIC_LIB) $(TEST_PROGRAM)

lint:
	cpplint *.hpp *.cpp