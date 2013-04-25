# Makefile for linked list prj
run: main.o list.o
	gcc -o run main.o list.o
stress: stress_test.o list.o
	gcc -o stress stress_test.o list.o
main.o: main.c
	gcc -c main.c
stress_test.o: stress_test.c
	gcc -c stress_test.c
list.o: list.c
	gcc -c list.c
clean:
	rm -f *.o run stress
