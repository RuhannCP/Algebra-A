all: main

main: function
	gcc -w main.c function.o -g -o main -Wunused-variable -lgmp

function: function.c
	gcc function.c -c -g -o function.o -Wunused-variable -lgmp

clean:
	-rm -rf *.o
mrproper: clean
	-rm -rf main

valgrind:
	valgrind ./main --leak-check=full