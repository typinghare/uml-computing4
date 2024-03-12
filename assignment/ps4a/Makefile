# C++ Compiler
COMPILER = g++

# C++ Flags
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g

# Libraries
LIB = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lboost_unit_test_framework

# Code source directory
SRC = ./

# Hpp files (dependencies)
DEPS = $(SRC)Universe.hpp \
       $(SRC)CelestialBody.hpp \
       $(SRC)NBodyConstant.hpp \
       $(SRC)Common.hpp \

# Static library
STATIC_LIB = NBody.a

# The object files that the static library includes
STATIC_LIB_OBJECTS = $(SRC)Universe.o \
				     $(SRC)CelestialBody.o \
				     $(SRC)Common.o

# Program
PROGRAM = NBody

# Program object files
MAIN_OBJECTS = $(SRC)main.o

# Test program
TEST_PROGRAM = test

# Test object files
TEST_OBJECTS = $(SRC)test.o

all: $(PROGRAM) $(TEST_PROGRAM)

$(SRC)%.o: $(SRC)%.cpp $(DEPS)
	$(COMPILER) $(CFLAGS) -c $<

$(PROGRAM): $(MAIN_OBJECTS) $(STATIC_LIB)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

$(STATIC_LIB): $(STATIC_LIB_OBJECTS)
	ar rcs $@ $^

$(TEST_PROGRAM): $(TEST_OBJECTS) $(STATIC_LIB)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm -f $(SRC)*.o $(PROGRAM) $(STATIC_LIB) $(TEST_PROGRAM)

lint:
	cpplint *.hpp *.cpp

boost: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM) < assets/data/planets.txt