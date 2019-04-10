all: main

main: listaencadeada.o
	g++ -w main.cpp listaencadeada.o -o main -std=c++11 -Wunused-variable

listaencadeada.o: listaencadeada.cpp
	g++ -c listaencadeada.cpp -o listaencadeada.o -Wunused-variable

clean:
	-rm -rf *.o
mrproper: clean
	-rm -rf main

