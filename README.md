projects
========

A simple and (relatively) fast brainfuck interpreter in C.
The reason I used a linked list instead of an array is that
I can expand the linked list infinitely in either direction
without having to destroy and recreate it each time. Based
on my tests, however, this seems to be somewhat less
performant than array-based implementations, likely because
it's not very cache-friendly.
