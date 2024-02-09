# C++ Compiler
COMPILER = g++

# C++ Flags
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g -I /opt/homebrew/include
# CFLAGS = --std=c++17 -Wall -Werror -pedantic -g

# Libraries
LIB = -L /opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system
# LIB = -lsfml-graphics -lsfml-window -lsfml-system

# Hpp files (dependencies)
DEPS = PTree.hpp

# Cpp files that should be compiled into object files
OBJECTS = PTree.o main.o

# Program
PROGRAM = PTree

.PHONY: all clean lint run

# Generate `PTree`
all: $(PROGRAM)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(COMPILER) $(CFLAGS) -c $<

# Run the PTree program and clean after running it
# Here, $(filter-out $@,$(MAKECMDGOALS)) passes all the arguments given to this
# target. It filters out the target name from the list of goals.
$(PROGRAM): $(OBJECTS)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

run: $(PROGRAM)
	./$(PROGRAM) 160 9 30 && make clean

# Clean all object files and program files
# "-f" flag refers to "force", which suppresses the "No such file or directory"
# warning
clean:
	rm -f *.o $(PROGRAM)

lint:
	cpplint *.hpp *.cpp
