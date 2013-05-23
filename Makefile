CC = g++
CFLAGS = -c -Wall

all: string

string: main.o vecop.o savevtk.o
	$(CC) main.o vecop.o savevtk.o -o string

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

vecop.o: vecop.cpp
	$(CC) $(CFLAGS) -c vecop.cpp

savevtk.o: savevtk.cpp
	$(CC) $(CFLAGS) -c savevtk.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp

test: test.o vecop.o
	$(CC) vecop.o test.o -o test

clean:
	rm -rf *.o string data.vtk test
