#include <fcntl.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE 1024

typedef struct {
	char word[42];
	unsigned count;
} WORD_T;

WORD_T *words = NULL;
size_t total_words = 0;

void print_and_free(WORD_T*, size_t, char*);
int comparator(const void *a, const void *b) {
	return strcmp(a, b);
}

int main(int argc, char **argv) {
	if (argc != 2) return -1;

	char *infile = argv[1];
	// TODO: open the file O_RDONLY
	if (fd == -1) return -2;

	// TODO: repeatedly call `read()` into a buffer of
	//       size BUFSIZE. Split the text in the buffer
	//       on newlines and spaces. For each token:
	//       search the `words` array to see if that
	//       word has already been added and if so
	//       increment the count. Otherwise add a new
	//       WORD_T struct to the end of the array of
	//       structs `words` and set the fields accordingly.

	// TODO: its possible that a word is split between
	//       one fill of the buffer and the next. You must
	//       move the last word at the end of the buffer to
	//       the beginning of the buffer and then fill
	//       the buffer from that point!

	print_and_free(words, total_words, infile);
	// TODO: close the file

	return 0;
}

void print_and_free(WORD_T *words, size_t total_words, char *infile) {
	int sum = 0;
	for (int i = 0; i < total_words; ++i) {
		if (words[i].count > 1)
			printf("%s: %u\n", words[i].word, words[i].count);
		sum += words[i].count;
	}
	printf("\n%d %s\n", sum, infile);

	free(words);
}

