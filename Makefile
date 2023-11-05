all: a2

a2: a2.o
	gcc -Wall -std=c99 -pedantic -o a2 a2.o


a2.c:
	gcc -c -Wall -std=c99 -pedantic a2.c

clean:
	rm -rfv *o a2
