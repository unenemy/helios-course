# Makefile for linked list prj
run: main.o list.o
	gcc -o run main.o list.o
main.o: main.c
	gcc -c main.c
list.o: list.c
	gcc -c list.c
clean:
	rm -f *.o run
