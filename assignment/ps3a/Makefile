# C++ Compiler
COMPILER = g++

# C++ Flags
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g -I /opt/homebrew/include
# CFLAGS = --std=c++17 -Wall -Werror -pedantic -g

# Libraries
LIB = -L /opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system
# LIB = -lsfml-graphics -lsfml-window -lsfml-system

# Hpp files (dependencies)
DEPS = Sokoban.hpp

# Cpp files that should be compiled into object files
OBJECTS = Sokoban.o main.o

# Program
PROGRAM = Sokoban

.PHONY: all clean lint run

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(COMPILER) $(CFLAGS) -c $<

$(PROGRAM): $(OBJECTS)
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LIB)

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -f *.o $(PROGRAM)

lint:
	cpplint *.hpp *.cpp