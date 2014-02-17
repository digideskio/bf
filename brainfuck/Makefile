CC	= cc
CFLAGS	= -Wall -Wextra -pedantic-errors -ansi
DFLAGS	= -g -pg
DIET	= /opt/diet/bin/diet

all: std
std: brainfuck.c
	$(CC) $(CFLAGS) -Ofast -o bf brainfuck.c
clean: brainfuck.c
	rm -f bf gmon.out
debug: brainfuck.c
	$(CC) $(CFLAGS) $(DFLAGS) -o bf brainfuck.c
release: brainfuck.c
	$(DIET) $(CC) -Ofast -static -o bf brainfuck.c
