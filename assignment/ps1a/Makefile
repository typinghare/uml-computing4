CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g -I /opt/homebrew/include
LIB =  -L /opt/homebrew/lib -lboost_unit_test_framework
#CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
#LIB = -lboost_unit_test_framework
DEPS = FibLFSR.hpp
OBJECTS = FibLFSR.o PhotoMagic.o
TEST_OBJECTS = FibLFSR.o test.o
PROGRAM = ps1
TEST_PROGRAM = test_program

.PHONY: all clean lint

all: $(PROGRAM)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@

$(TEST_PROGRAM): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o $(PROGRAM) $(TEST_PROGRAM)

lint:
	cpplint *.cpp *.hpp

# Create a PhotoMagi.a static library containing FibLFSR.o and PhotoMagic.o
static: $(PROGRAM)
	ar rcs PhotoMagic.a ${OBJECTS}

# Run the main function
PhotoMagic: $(PROGRAM)
	./$(PROGRAM)

# Run all tests with Boost
test: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)