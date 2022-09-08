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
	char buf[BUFSIZE];
	char* temp = NULL;
	char last_word[BUFSIZE] = ""; 
	char last_char = 0;
	char* p = buf;
	
	buf_size = read(fd, buf, BUFSIZE-1);
	buf[buf_size] = 0;
	while(buf_size > 0) {
		char* delim = " \t\n";
		// Case 1: buf ended up spliting a word
		if(buf[0] !=  ' ' &&  buf[0] !=  '\t' && buf[0] !=  '\n' && last_char !=  ' ' &&  last_char !=  '\t' && last_char !=  '\n' && strlen(last_word) != 0) {
			char* end_of_word = strsep(&p, delim); 
			strncat(last_word, end_of_word, strlen(last_word)+strlen(end_of_word)+1);
			
		}
		
		// Case 2: buf ended on a whitespace  
		// Do nothing
	
		
		last_char = buf[buf_size-1];
		if(temp == NULL) { 
			temp = strsep(&p, delim);
		} else {
			temp = last_word;
		}
		
		while(p != NULL) {
			if(strlen(temp) > 0 ) {
				total_words++;
				printf("%s\n", temp);
			}
			/*
			//Use lfind to search word array for temp word
			if(//already in words array && temp !=NULL){
				//add to count

			} else if(//not in words array && !=NULL) {
			total_word++;
				//realloc 
			}
		*/
			temp = strsep(&p, delim);
			
		}
		
		//printf("%s", buf);
		strcpy(last_word, temp);	
		buf_size = read(fd, buf, BUFSIZE-1);
		buf[buf_size] = 0;
		p = buf;
		
	}
	
	if(buf_size == -1) {
		printf("Error reading file");
	} else if(buf_size == 0) {
		printf("Finished Reading file\n");
		printf("%ld\n", total_words);
	}
	//print_and_free(words, total_words, infile);
	// TODO: close the file
	close(fd);

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

