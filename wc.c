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
	const char** aptr = (const char**) a;
	WORD_T* bptr = (WORD_T*) b;
	return strcmp(*aptr, bptr->word);
}

int main(int argc, char **argv) {
	if (argc != 2) return -1;

	char *infile = argv[1];
	// TODO: open the file O_RDONLY
	int fd = open(infile, O_RDONLY);
	
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
	ssize_t buf_size;
	char* buf = malloc(BUFSIZE*sizeof(char));
	char* token = NULL;
	size_t element_size = sizeof(WORD_T); 
	
	char last_word[BUFSIZE] = ""; 
	char last_char = 0;
	
	buf_size = read(fd, buf, BUFSIZE-1);
	buf[buf_size] = 0;
	char *stringp = buf;
	
	while(buf_size > 0) {
		char* delim = " \t\n";
		// Case 1: buf ended up spliting a word
		if(buf[0] !=  ' ' &&  buf[0] !=  '\t' && buf[0] !=  '\n' && last_char !=  ' ' &&  last_char !=  '\t' && last_char !=  '\n' && strlen(last_word) != 0) {
			char* end_of_word = strsep(&stringp, delim); 
			strncat(last_word, end_of_word, strlen(last_word)+strlen(end_of_word)+1);
			
		}
		
		// Case 2: buf ended on a whitespace  
		// Do nothing
	
		
		last_char = buf[buf_size-1];
		if(token == NULL) { 
			token = strsep(&stringp, delim);
		} else {
			token = last_word;
		}
		
		//Using lfind to search word array for temp word
		WORD_T* ptr = NULL;
		
		
		while(stringp != NULL) {
			
			if(token != NULL && strlen(token) > 0) {				
				if(words != NULL) 
					ptr = lfind(&token, words, &total_words, element_size, comparator);
					
				if(ptr != NULL) {
					// If found increment word count
					ptr->count++;

				} else {
					// Realloc and incement total_words count
					words = realloc(words, sizeof(WORD_T) * ++total_words);
					// Inialize string to all nulls
					//strncpy(words[total_words - 1].word, "", 42);
					// Copy token to words array and set count
					strncpy(words[total_words - 1].word, token, 42);
					
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
	
	// TODO: close the file and free buf
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
	printf("\n%d %s\n", sum, infile);

	free(words);
}

