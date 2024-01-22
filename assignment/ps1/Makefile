CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g -I /opt/homebrew/include
LIB =  -L /opt/homebrew/lib -lboost_unit_test_framework
#CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
#LIB = -lboost_unit_test_framework
# Your .hpp files
DEPS = FibLFSR.hpp
# Your compiled .o files
OBJECTS = FibLFSR.o test.o
# The name of your program
PROGRAM = ps1

.PHONY: all clean lint

all: $(PROGRAM)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o $(PROGRAM)

lint:
	cpplint --filter=-build/include_subdir *.cpp *.hpp
