all: clean
	gcc -o bf -Wall -Wextra -pedantic -ansi -Ofast brainfuck.c
clean:
	rm -f bf
debug: clean
	gcc -o bf -Wall -Wextra -pedantic -ansi -g -pg brainfuck.c
release: clean
	/opt/diet/bin/diet gcc -o bf -Wall -Wextra -pedantic-errors -ansi -Ofast -static brainfuck.c
