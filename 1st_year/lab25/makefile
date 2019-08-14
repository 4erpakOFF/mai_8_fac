#makefile for 25-26 lab
CC=gcc
LD=gcc
CFLAGS=-g -Wall -pedantic -std=c99
LDFLAGS=
SOURCES=main.c list.c insert_sort.c
HEADERS=list.h insert_sort.h
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=sort

sort: main.o list.o insert_sort.o
	$(CC) -o $(EXECUTABLE) main.o list.o insert_sort.o

main.o: main.c list.h insert_sort.h
	$(CC) -c main.c 
list.o: list.c list.h
	$(CC) -c list.c

insert_sort.o: insert_sort.c insert_sort.h
	$(CC) -c insert_sort.c

rm_obj:
	rm -rf $(OBJECTS) *.h.gch 

clean:
	rm -rf $(EXECUTABLE) *.o *.h.gch
