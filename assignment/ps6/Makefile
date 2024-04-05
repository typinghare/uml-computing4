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
	   $(SRC)SymbolTable.hpp

# Static library
STATIC_LIB = TextWriter.a

# The object files that the static library includes
STATIC_LIB_OBJECTS = $(SRC)RandWriter.o

# Program
PROGRAM = TextWriter

# Program object files
MAIN_OBJECTS = $(SRC)TextWriter.o

# Test program
TEST_PROGRAM = test

# Test object files
TEST_OBJECTS = $(SRC)test.o

# WordWriter program
WORD_WRITER_PROGRAM = WordWriter

# WordWriter object files
WORD_WRITER_PROGRAM_OBJECTS = $(SRC)WordWriter.o $(SRC)AdvancedTextWriter.o

all: $(PROGRAM) $(TEST_PROGRAM)

$(SRC)%.o: $(SRC)%.cpp $(DEPS)
	$(COMPILER) $(CFLAGS) -c $<

$(PROGRAM): $(MAIN_OBJECTS) $(STATIC_LIB)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

$(STATIC_LIB): $(STATIC_LIB_OBJECTS)
	ar rcs $@ $^

$(TEST_PROGRAM): $(TEST_OBJECTS) $(STATIC_LIB)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

$(WORD_WRITER_PROGRAM): $(WORD_WRITER_PROGRAM_OBJECTS)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm -f $(SRC)*.o $(PROGRAM) $(STATIC_LIB) $(TEST_PROGRAM) $(WORD_WRITER_PROGRAM)

lint:
	cpplint *.hpp *.cpp

boost: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

run-input17: $(PROGRAM)
	./$(PROGRAM) 2 11 < input17.txt

run-romeo: $(PROGRAM)
	./$(PROGRAM) 3 100 < romeo.txt

run-tomsawyer: $(PROGRAM)
	./$(PROGRAM) 8 400 < tomsawyer.txt

run-word-romeo: $(WORD_WRITER_PROGRAM)
	./$(WORD_WRITER_PROGRAM) 2 50  < romeo.txt

run-word-tomsawyer: $(WORD_WRITER_PROGRAM)
	./$(WORD_WRITER_PROGRAM) 2 150  < tomsawyer.txt