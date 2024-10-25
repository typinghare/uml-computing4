COMPILER = g++
OPTS = -std=c++20 -Wall -Werror -pedantic -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
DEPS = penta.hpp
OBJECTS = penta.o main.o
PROGRAM = Penta

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(COMPILER) $(OPTS) -c $<

$(PROGRAM): $(OBJECTS)
	$(COMPILER) $(OPTS) -o $@ $^ $(LIBS)

clean:
	rm -f *.o $(PROGRAM)

run: $(PROGRAM)
	./$<