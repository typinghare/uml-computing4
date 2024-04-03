# C++ Compiler
COMPILER = g++

# C++ Flags (C++ version: 20)
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g

# Libraries
LIB = -lboost_unit_test_framework

# Code source directory
SRC = ./

# Hpp files (dependencies)
DEPS = $(SRC)RandWriter.hpp \
	   $(SRC)FrequencyStore.hpp

# Static library
STATIC_LIB = RandWritten.a

# The object files that the static library includes
STATIC_LIB_OBJECTS = $(SRC)RandWriter.o \
				     $(SRC)FrequencyStore.o

# Program
PROGRAM = TextWriter

# Program object files
MAIN_OBJECTS = $(SRC)TextWriter.o

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

run-input17: $(PROGRAM)
	./$(PROGRAM) 2 11 < assets/input17.txt

run-romeo: $(PROGRAM)
	./$(PROGRAM) 4 100 < assets/romeo.txt

run-tomsawyer: $(PROGRAM)
	./$(PROGRAM) 7 400 < assets/tomsawyer.txt