CC	:= cc
SRC	:= bf.c
CFLAGS	:= -Wall -Wextra -pedantic-errors -ansi
DFLAGS	:= -g -pg -O0
INSTALL	:= /usr/local/bin/bf
OUT	:= bf

all:	std

std:	$(SRC)
	$(CC) $(CFLAGS) -O3 -o $(OUT) $?

clean:	$(SRC)
	rm -f $(OUT) gmon.out

debug:	$(SRC)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(OUT) $?

install: std
	install $(OUT) $(INSTALL)
	strip $(INSTALL)
