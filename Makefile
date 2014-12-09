CC=clang++
CFLAGS=-c -Wall
LDFLAGS=-lGL -lGLEW -lSDL
SOURCES=$(wildcard *.c *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Geometry

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o Geometry

.PHONY: all clean
