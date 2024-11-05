CC = g++
OPTS = --std=c++20 -Wall -Werror -pedantic -g
LIBS = -lsfml-system -lsfml-window -lsfml-graphics
DEPS = Sokoban.hpp
OBJECTS = Sokoban.o main.o
PROGRAM = Sokoban

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(OPTS) -c $^

$(PROGRAM): $(OBJECTS)
	$(CC) $(OPTS) -o $@ $^ $(LIBS)

test: $(PROGRAM)
	./$< ../assets/level/level4.lvl

clean:
	rm -f $(PROGRAM) *.o *.gch
