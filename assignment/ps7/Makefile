# C++ Compiler
COMPILER = g++

# C++ Flags (C++ version: 20)
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g

# Libraries
LIB = -lboost_unit_test_framework -lboost_date_time

# Code source directory
SRC = ./

# Hpp files (dependencies)
DEPS = $(SRC)LogPattern.hpp

# Program
PROGRAM = ps7

# Program object files
MAIN_OBJECTS = $(SRC)main.o

all: $(PROGRAM)

$(SRC)%.o: $(SRC)%.cpp $(DEPS)
	$(COMPILER) $(CFLAGS) -c $<

$(PROGRAM): $(MAIN_OBJECTS) 
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm -f $(SRC)*.o $(PROGRAM) $(STATIC_LIB) $(TEST_PROGRAM)

lint:
	cpplint *.hpp *.cpp

run: $(PROGRAM)
	./$(PROGRAM) logs/device5_intouch.log

run-all: $(PROGRAM)
	./$(PROGRAM) logs/device1_intouch.log && \
	./$(PROGRAM) logs/device2_intouch.log && \
	./$(PROGRAM) logs/device3_intouch.log && \
	./$(PROGRAM) logs/device4_intouch.log && \
	./$(PROGRAM) logs/device5_intouch.log && \
	./$(PROGRAM) logs/device6_intouch.log &&