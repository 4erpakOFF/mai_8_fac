CC=gcc -std=c99
FLAGS=-pedantic -Wall -o lab.out -g
HEADERS=parser.h text_processor.h one_com.h
SOURCES=main.c parser.c text_processor.c one_com.c

all: lab.out

lab: $(SOURCES) $(HEADERS)
	$(CC) $(FLAGS) $(SOURCES)
