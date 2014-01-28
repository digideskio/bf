#No wizardry here
all: clean
	gcc -o bf -Wall -pedantic -ansi -Ofast brainfuck.c
clean:
	rm -f bf
debug: clean
	gcc -o bf -Wall -pedantic -ansi -g -pg brainfuck.c
