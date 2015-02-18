CC=g++
CFLAGS=-c -g -Wall -Dmain=SDL_main
LDFLAGS=-I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2main -lSDL2 -lSDL2_image
SOURCES=model.cpp view.cpp controller.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lab4.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) -g $(SOURCES) $(LDFLAGS) -o $@

clean:
	rm $(EXECUTABLE)
