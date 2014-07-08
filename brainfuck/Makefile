CC	:= cc
CFLAGS	:= -Wall -Wextra -pedantic-errors -ansi
DFLAGS	:= -g -pg -O0
INSTALL	:= /usr/local/bin/bf
DIET	:= /opt/diet/bin/diet
OUT	:= bf

all: std
std: brainfuck.c
	$(CC) $(CFLAGS) -O3 -o $(OUT) $?
clean: brainfuck.c
	rm -f $(OUT) gmon.out
debug: brainfuck.c
	$(CC) $(CFLAGS) $(DFLAGS) -o $(OUT) $?
diet: brainfuck.c
	$(DIET) $(CC) $(CFLAGS) -Ofast -static -o $(OUT) $?
	strip $(OUT)
install: std
	install $(OUT) $(INSTALL)
	strip $(INSTALL)
