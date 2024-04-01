# C++ Compiler
COMPILER = g++

# C++ Flags (C++ version: 20)
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g -O3

# Libraries
LIB = -lsfml-system -lboost_unit_test_framework

# Code source directory
SRC = ./

# Hpp files (dependencies)
DEPS = $(SRC)EDistance.hpp \
	   $(SRC)AbstractEDistance.hpp \
	   $(SRC)NeedlemanWunschEDistance.hpp \
	   $(SRC)OptimizedEDistance.hpp \
	   $(SRC)HirshbergEDistance.hpp

# Static library
STATIC_LIB = EDistance.a

# The object files that the static library includes
STATIC_LIB_OBJECTS = $(SRC)EDistance.o \
					 $(SRC)AbstractEDistance.o \
					 $(SRC)NeedlemanWunschEDistance.o \
					 $(SRC)OptimizedEDistance.o \
					 $(SRC)HirshbergEDistance.o

# Program
PROGRAM = EDistance

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
	./$(PROGRAM) < sequence/example10.txt
