all: main

main: function.o
	g++ -w main.c function.o -o main -Wunused-variable -lgmp

function.o: function.c
	g++ function.c -c -g -o function.o -Wunused-variable -lgmp

clean:
	-rm -rf *.o
mrproper: clean
	-rm -rf main

