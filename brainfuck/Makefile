CC	= cc
CFLAGS	= -Wall -Wextra -pedantic-errors -ansi
DFLAGS	= -g -pg
INSTALL	= /usr/local/bin/bf
DIET	= /opt/diet/bin/diet

all: std
std: brainfuck.c
	$(CC) $(CFLAGS) -Ofast -o bf brainfuck.c
clean: brainfuck.c
	rm -f bf gmon.out
debug: brainfuck.c
	$(CC) $(CFLAGS) $(DFLAGS) -o bf brainfuck.c
diet: brainfuck.c
	$(DIET) $(CC) $(CFLAGS) -Ofast -static -o bf brainfuck.c
	strip bf
install: std
	install bf $(INSTALL)
	strip $(INSTALL)
