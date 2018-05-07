CFLAGS = -Wall -fpic -coverage -lm

run: testme
	./testme testme.c

testme:	testme.o
	gcc -o testme testme.c $(CFLAGS)

all: testme