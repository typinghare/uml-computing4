# C++ Compiler
COMPILER = g++

# C++ Flags
#CFLAGS = --std=c++17 -Wall -Werror -pedantic -g -I /opt/homebrew/include
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g

# Libraries
#LIB = -L /opt/homebrew/lib -lboost_unit_test_framework
LIB = -lboost_unit_test_framework

# Hpp files (dependencies)
DEPS = FibLFSR.hpp

# Cpp files that should be compiled into object files
OBJECTS = FibLFSR.o PhotoMagic.o
TEST_OBJECTS = FibLFSR.o test.o

# Programs
PROGRAM_PHOTO_MAGIC = PhotoMagic
PROGRAM_TEST = test

# Static library
STATIC_LIB = PhotoMagic.a

.PHONY: all clean lint

all: $(PROGRAM_TEST) $(PROGRAM_PHOTO_MAGIC)

# Wildcard recipe to make .o files from corresponding .cpp file
# Note: this command matches .cpp file one by one, and "$<" here refers to the
# first prerequisite, which is the .cpp file matched.
%.o: %.cpp $(DEPS)
	$(COMPILER) $(CFLAGS) -c $<

# Program `PhotoMagic`
$(PROGRAM_PHOTO_MAGIC): $(STATIC_LIB)
	$(COMPILER) $(CFLAGS) -o $@ "./${STATIC_LIB}" $(LIB)

# Program `test`
$(PROGRAM_TEST): $(TEST_OBJECTS)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

# Create a PhotoMagi.a static library containing FibLFSR.o and PhotoMagic.o
$(STATIC_LIB): $(OBJECTS)
	ar rcs $(STATIC_LIB) $(OBJECTS)

# Run the PhotoMagic program and clean after running it
runPhotoMagic: $(PROGRAM_PHOTO_MAGIC)
	./$(PROGRAM_PHOTO_MAGIC) && make clean

# Run all tests with Boost and clean after running it
runTest: $(PROGRAM_TEST)
	./$(PROGRAM_TEST) && make clean

# Clean all object files and program files
# "-f" flag refers to "force", which suppresses the "No such file or directory"
# warning
clean:
	rm -f *.o $(STATIC_LIB) $(PROGRAM_PHOTO_MAGIC) $(PROGRAM_TEST)

# Use cpplint
lint:
	cpplint *.cpp *.hpp