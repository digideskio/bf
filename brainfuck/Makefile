CC	= cc
CFLAGS	= -Wall -Wextra -pedantic-errors -ansi -march=native
DFLAGS	= -g -pg
INSTALL	= /usr/local/bin/bf
DIET	= /opt/diet/bin/diet
OUT	= bf

all: std
std: brainfuck.c
	$(CC) $(CFLAGS) -O3 -o $(OUT) $?
clean: brainfuck.c
	rm -f bf gmon.out
debug: brainfuck.c
	$(CC) $(CFLAGS) $(DFLAGS) -o $(OUT) $?
diet: brainfuck.c
	$(DIET) $(CC) $(CFLAGS) -O3 -static -o $(OUT) $?
	strip bf
install: std
	install bf $(INSTALL)
	strip $(INSTALL)
