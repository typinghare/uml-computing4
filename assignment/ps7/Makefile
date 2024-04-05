# C++ Compiler
COMPILER = g++

# C++ Flags (C++ version: 20)
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g

# Libraries
LIB = -lboost_unit_test_framework -lboost_date_time

# Code source directory
SRC = ./

# Hpp files (dependencies)
DEPS =

# The object files that the static library includes
STATIC_LIB_OBJECTS = $(SRC)ps7.cpp

# Program
PROGRAM = ps7

# Program object files
MAIN_OBJECTS = $(SRC)ps7.o

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
	./$(PROGRAM) logs/device5_intouch.log