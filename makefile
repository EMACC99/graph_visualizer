CC=g++
CFLAGS=-c -Wall -Wpedantic -Wextra -Wno-sign-compare -Wno-maybe-uninitialized -std=c++17 -Ofast
LDFLAGS=
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sfml-app
BINDIR=/usr/bin

all: $(SOURCES) $(EXECUTABLE)
        
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBFLAGS)

clean:
	rm *.o $(EXECUTABLE)

# install:
# 	#install -s $(EXECUTABLE) $(BINDIR)
# 	sudo cp -u $(EXECUTABLE) $(BINDIR)
# uninstall:
# 	sudo rm $(BINDIR)/$(EXECUTABLE)
