#include <stdio.h>
#include <stdlib.h>

/*
 * A simple and fast brainfuck interpreter in C.
 * The reason I used a linked list instead of an array is that
 * I can expand the linked list infinitely in either direction
 * without having to destroy and recreate it each time.
 *
 * TODO:
 * 1. Make it ignore non-code characters when it loads the program
 *    (as opposed to while running it)
 * 2. Allocate larger blocks of memory and carve nodes out of that
 *    instead of doing a malloc() every time we need a new node
 */

struct node {
	char c;
	struct node* prev;
	struct node* next;
};

void interpret(struct node* ptr, char* str, size_t fsize)
{
	/*
	 * Note that while we move i sequentially through each instruction stored in str,
	 * it does jump around because of the [ and ] instructions. Just think of it like
	 * the instruction pointer and [ and ] as jmp.
	 */
	size_t i;
	for (i = 0; i < fsize; ++i) {
		size_t parens;
		switch(str[i]) {
			case '+':
				++ptr->c;
				break;
			case '-':
				--ptr->c;
				break;
			case '<':
				if (ptr->prev == 0) {
					ptr->prev = (struct node*) malloc(sizeof(struct node));
					ptr->prev->c = 0;
					ptr->prev->prev = 0;
					ptr->prev->next = ptr;
				}
				ptr = ptr->prev;
				break;
			case '>':
				if (ptr->next == 0) {
					ptr->next = (struct node*) malloc(sizeof(struct node));
					ptr->next->c = 0;
					ptr->next->prev = ptr;
					ptr->next->next = 0;
				}
				ptr = ptr->next;
				break;
			case '.':
				putchar(ptr->c);
				break;
			case ',':
				ptr->c = getchar();
				break;
			case '[':
				if (ptr->c == 0) {
					parens = 1;
					do {
						++i;
						if (str[i] == '[')
							++parens;
						if (str[i] == ']')
							--parens;
					} while (parens != 0 && i < fsize);
				}
				break;
			case ']':
				if (ptr->c != 0) {
					parens = 1;
					do {
						--i;
						if (str[i] == ']')
							++parens;
						if (str[i] == '[')
							--parens;
					} while (parens != 0 && i >= 0);
				}
		}
	}
}

int main(int argc, char *argv[])
{
	struct node* ptr;
	FILE *fp;
	size_t fsize, i;
	char c;
	char* str;

	if (argc != 2) {
		printf("usage: %s SOURCEFILE\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (!(fp = fopen(argv[1], "r"))) {
		printf("%s: error: could not open file\n", argv[0]);
		return EXIT_FAILURE;
	}

	ptr = (struct node*) malloc(sizeof(struct node));
	ptr->c = 0;
	ptr->prev = 0;
	ptr->next = 0;

	fseek(fp, 0L, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	str = (char*) malloc(fsize);
	i = 0;
	while ((c = fgetc(fp)) != EOF) {
		str[i] = c;
		++i;
	}

	interpret(ptr, str, fsize);

	/* move to beginning of list to prepare for cleanup */
	while (ptr->prev != 0)
		ptr = ptr->prev;

	while (ptr != 0) {
		struct node* tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	
	free(str);
	fclose(fp);

	return EXIT_SUCCESS;
}
