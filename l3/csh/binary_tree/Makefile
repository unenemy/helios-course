# Makefile for balanced binary search tree
run: main.o bbst.o bbst.so
	gcc -o run main.o bbst.o
stress: stress.o bbst.o
	gcc -o stress stress.o bbst.o
stress.o: stress.c
	gcc -c stress.c
main.o: main.c
	gcc -c main.c
bbst.o: bbst.c
	gcc -c -Wall -Werror -fpic bbst.c
bbst.so:
	gcc -shared -o bbst.so bbst.o
clean:
	rm -f *.o run stress *.so
