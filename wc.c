#include <fcntl.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE 1024
#define STRSIZE 42

typedef struct {
	char word[STRSIZE];
	unsigned count;
} WORD_T;

WORD_T *words = NULL;
size_t total_words = 0;

void print_and_free(WORD_T*, size_t, char*);

int comparator(const void *a, const void *b) {
	const char** aptr = (const char**) a;
	WORD_T* bptr = (WORD_T*) b;
	return strcmp(*aptr, bptr->word);
}

int main(int argc, char **argv) {
	// Opening file
	if (argc != 2) return -1;
	char *infile = argv[1];
	int fd = open(infile, O_RDONLY);
	if (fd == -1) return -2;
	
	// Buffer
	ssize_t buf_size;
	char* buf = malloc(BUFSIZE*sizeof(char));
	char* token = NULL;
	size_t element_size = sizeof(WORD_T); 
	
	char last_word[BUFSIZE] = ""; 
	char last_char = 0;
	
	buf_size = read(fd, buf, BUFSIZE-1);
	buf[buf_size] = 0;
	char *stringp = buf;
	
	// Read and store buffer data
	while(buf_size > 0) {
		char* delim = " \t\n";
		// Case 1: buf ended up spliting a word
		if(buf[0] !=  ' ' &&  buf[0] !=  '\t' && buf[0] !=  '\n' && last_char !=  ' ' &&  last_char !=  '\t' && last_char !=  '\n' && strlen(last_word) != 0) {
			char* end_of_word = strsep(&stringp, delim); 
			strncat(last_word, end_of_word, strlen(last_word)+strlen(end_of_word)+1);
			
		}
		
		// Case 2: buf ended on a whitespace  
		// Do nothing
	
		// Moving last word to front of buffer if not first read
		last_char = buf[buf_size-1];
		if(token == NULL) { 
			token = strsep(&stringp, delim);
		} else {
			token = last_word;
		}
		
		WORD_T* ptr = NULL;
		
		while(stringp != NULL) {
			
			if(token != NULL && strlen(token) > 0) {				
				if(words != NULL) 
					// Look for word in struct array
					ptr = lfind(&token, words, &total_words, element_size, comparator);
					
				if(ptr != NULL) {
					// If found increment word count
					ptr->count++;

				} else {
					// Realloc and incement total_words count
					words = realloc(words, sizeof(WORD_T) * ++total_words);
					// Make new word in struct array;
					strncpy(words[total_words - 1].word, token, STRSIZE);
					words[total_words - 1].count = 1;
				}
				
				
				
			}
			token = strsep(&stringp, delim);
		}

		strcpy(last_word, token);	
		buf_size = read(fd, buf, BUFSIZE-1);
		buf[buf_size] = 0;
		stringp = buf;
		
	}
	
	if(buf_size == -1) {
		printf("Error reading file");
	}
	
	print_and_free(words, total_words, infile);
	
	close(fd);
	free(buf);

	return 0;
}

void print_and_free(WORD_T *words, size_t total_words, char *infile) {
	int sum = 0;
	for (int i = 0; i < total_words; ++i) {
		if (words[i].count > 1)
			printf("%s: %u\n", words[i].word, words[i].count);
		sum += words[i].count;
	}
	printf("\n%d %s\n\n", sum, infile);

	free(words);
}

