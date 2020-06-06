CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lGL -lGLEW -lSDL -lSDL_mixer
SOURCES=$(wildcard *.c *.cpp Utility/*.cpp)
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
