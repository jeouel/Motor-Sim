all: ngin

ngin: main.o
	g++ -o ngin main.o

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o ngin
