/*
 * bf: A simple and (relatively) fast brainfuck interpreter in C.
 *
 * The reason I used a linked list instead of an array is that
 * I can expand the linked list infinitely in either direction
 * without having to destroy and recreate it each time. Based
 * on my tests, however, this seems to be somewhat less
 * performant than array-based implementations, likely because
 * it's not very cache-friendly.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * This would be in stdint.h, but that was introduced in C99,
 * so we're going to define it outselves just to be safe.
 */
#ifdef SIZE_MAX
#undef SIZE_MAX
#endif

#define SIZE_MAX ((size_t) -1)

struct node {
	unsigned char c;
	struct node *prev;
	struct node *next;
};

/*
 * Interprets and runs brainfuck code.
 * All characters that are not brainfuck commands are ignored.
 *
 * args: pointer to first node, string to be interpreted, size of string
 * returns: 0 on success, 1 for invalid program, 2 for bad memory allocation
 */
static int interpret(struct node *ptr, char *str, size_t fsize)
{
	size_t i;
	long bal = 0;

	/*
	 * Note that while we move i sequentially through each
	 * instruction stored in str, it does jump around because
	 * of the [ and ] instructions. Just think of it like the
	 * instruction pointer and [ and ] as jmp.
	 *
	 * Also note that str isn't technically a C string since
	 * it isn't null-terminated, but that's OK because we
	 * know its size.
	 */

	for (i = 0; i < fsize; ++i) {
		switch (str[i]) {
		case '+':
			++ptr->c;
			break;
		case '-':
			--ptr->c;
			break;
		case '<':
			if (ptr->prev == 0) {
				ptr->prev = (struct node *)
					malloc(sizeof(struct node));
				if (ptr->prev == NULL)
					return 2;
				ptr->prev->c = 0;
				ptr->prev->prev = NULL;
				ptr->prev->next = ptr;
			}
			ptr = ptr->prev;
			break;
		case '>':
			if (ptr->next == 0) {
				ptr->next = (struct node *)
					malloc(sizeof(struct node));
				if (ptr->next == NULL)
					return 2;
				ptr->next->c = 0;
				ptr->next->prev = ptr;
				ptr->next->next = NULL;
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
				bal = 1;
				do {
					++i;
					if (str[i] == '[')
						++bal;
					if (str[i] == ']')
						--bal;
				} while (bal && i < fsize - 1);
			}
			break;
		case ']':
			if (ptr->c != 0) {
				bal = 1;
				do {
					--i;
					/*
					 * some evil programs
					 * could cause i to
					 * underflow here
					 */
					if (i >= fsize)
						return 1;
					if (str[i] == ']')
						++bal;
					if (str[i] == '[')
						--bal;
				} while (bal);
			}
			break;
		default:
			break; /* nothing */
		}
	}

	/* the program is invalid if all brackets don't match at the end */
	return bal ? 1 : 0;
}

#define ERROR(msg) \
	do { \
		printf("%s: error: %s\n", argv[0], msg); \
		ret = EXIT_FAILURE; \
		goto cleanup; \
	} while (0)

int main(int argc, char *argv[])
{
	struct node *ptr, *tmp;
	FILE *fp;
	long fsize;
	char *str = NULL;
	int status, ret = EXIT_SUCCESS;

	/*
	 * These first few error checks don't use the
	 * macro because there's nothing to clean up,
	 * and calling fclose() on an uninitialized
	 * file pointer is a no-no.
	 */

	if (setvbuf(stdout, NULL, _IONBF, 0)) {
		printf("%s: error: could not unbuffer stdout\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (argc != 2) {
		printf("usage: %s SOURCEFILE\n", argv[0]);
		return EXIT_FAILURE;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("%s: error: could not open file\n", argv[0]);
		return EXIT_FAILURE;
	}

	ptr = (struct node *) malloc(sizeof(struct node));
	if (ptr == NULL)
		ERROR("bad memory allocation");

	ptr->c = 0;
	ptr->prev = NULL;
	ptr->next = NULL;

	if (fseek(fp, 0L, SEEK_END))
		ERROR("cannot read file");

	fsize = ftell(fp);
	if (fsize == -1)
		ERROR("cannot read file");

	if (fseek(fp, 0L, SEEK_SET))
		ERROR("cannot read file");

	if ((unsigned long) fsize > SIZE_MAX)
		ERROR("file too large");

	str = (char *) malloc(fsize);
	if (str == NULL)
		ERROR("bad memory allocation");

	if (fread(str, sizeof(char), fsize, fp) != (size_t) fsize)
		ERROR("cannot read file");

	status = interpret(ptr, str, fsize);

	if (status == 1)
		ERROR("unmatched brackets");
	else if (status == 2)
		ERROR("bad memory allocation");

cleanup:
	/* move to beginning of list to prepare for cleanup */
	while (ptr->prev)
		ptr = ptr->prev;

	while (ptr) {
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}

	free(str);
	fclose(fp);

	return ret;
}
