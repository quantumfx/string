CC = g++
CFLAGS = -c -Wall

all: string

string: main.o vecop.o
	$(CC) main.o vecop.o -o string

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

vecop.o: vecop.cpp
	$(CC) $(CFLAGS) -c vecop.cpp

clean:
	rm -rf *.o string
