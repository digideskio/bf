CC	:= cc
SRC	:= bf.c
CFLAGS	:= -Wall -Wextra -pedantic-errors -ansi
DFLAGS	:= -g -pg -O0
INSTALL	:= /usr/local/bin/bf
OUT	:= bf

all:	$(OUT)

$(OUT):	$(SRC)
	$(CC) $(CFLAGS) -O3 -o $@ $?

clean:
	rm -f $(OUT) gmon.out

debug:	$(SRC)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(OUT) $?

install: bf
	install $(OUT) $(INSTALL)
	strip $(INSTALL)
