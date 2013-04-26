# Makefile for balanced binary search tree
run: main.o bbst.o
	gcc -o run main.o bbst.o
main.o: main.c
	gcc -c main.c
bbst.o: bbst.c
	gcc -c bbst.c
clean:
	rm -f *.o run
