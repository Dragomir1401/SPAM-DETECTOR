#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#define BUFF_SIZE 50

void verify_email(words **output, int **emails_size, int **caps_size,
				  int **email_chars, int **spammer, int **email_punc,
				  int **max_newline, new_words **added)
{
	// Open keywords file and check succes of operation
	FILE *keywords_file = fopen("data/keywords", "r");
	if (!keywords_file) {
		printf("Failed to load Keywords.\n");
		exit(EXIT_FAILURE);
	} // Alloc buffer to read from file
	char *str = malloc(BUFF_SIZE * sizeof(char));
	if (!str) {
		printf("Cant alloc memory"); exit(EXIT_FAILURE);
	} // Read nr of keywords
	int nr_keywords;
	fscanf(keywords_file, "%d\n", &nr_keywords);
	// Alloc struct for keywords
	(*output) = malloc(nr_keywords * sizeof(words));
	if ((*output) == NULL) {
		printf("Cant alloc memory"); exit(EXIT_FAILURE);
	}
	// Get each keyword line by line
	for (int i = 0; i < nr_keywords; i++) {
		fgets(str, BUFF_SIZE, keywords_file);
		if (i != nr_keywords - 1) // Put '\0' as end of string
			str[strlen(str) - 1] = '\0';
		// Alloc space for each keyword
		(*output)[i].keyword = malloc(BUFF_SIZE * sizeof(char));
		if (!((*output)[i].keyword)) {
			printf("Cant alloc memory\n"); free(*output); exit(EXIT_FAILURE);
		}
		// Copy keyword in struct
		strcpy((*output)[i].keyword, str);
		// Initialise values we will need later
		(*output)[i].appearances = 0; (*output)[i].deviation = 0;
		(*output)[i].nr_words = nr_keywords;
	}
	// Open additional keywords file
	FILE *more_keywords_file = fopen("more_keywords", "r");
	if (!more_keywords_file) {
		printf("Failed to load Keywords.\n"); exit(EXIT_FAILURE);
	} // Read nr of additional keywords
	int nr_keywords1;
	fscanf(more_keywords_file, "%d\n", &nr_keywords1);
	// Alloc size of each new keyword
	(*added) = malloc(nr_keywords1 * sizeof(new_words));
	if ((*added) == NULL) {
		printf("Cant alloc memory"); exit(EXIT_FAILURE);
	}
	// Get each additional keyword line by line with a buffer
	for (int i = 0; i < nr_keywords1; i++) {
		fgets(str, BUFF_SIZE, more_keywords_file);
		if (i != nr_keywords1 - 1) // Put '\0' as string terminator
			str[strlen(str) - 1] = '\0';
		// Alloc size for each additional keyword
		(*added)[i].more_keywords = malloc(BUFF_SIZE * sizeof(char));
		if (!((*added)[i].more_keywords)) {
			printf("Cant alloc memory\n"); free(*added); exit(EXIT_FAILURE);
		}
		// Copy each additional keyword to struct
		strcpy((*added)[i].more_keywords, str);
		// Initialise values we will need later
		(*added)[i].new_appereances = 0;
		(*added)[i].nr_new_words = nr_keywords1;
	}
	// Functions which counts nr of email and alloc memeory
	open_directory_alloc(output, emails_size, caps_size, email_chars, spammer,
						 email_punc, max_newline);
	// Counts each keyword and additional keyword appereance in each email
	for (int i = 0; i < nr_keywords; i++)
		count_keywords(output, i);
	for (int i = 0; i < nr_keywords1; i++)
		count_more_keywords(added, i, output);
	// Measure email size in words, characters, uppercases, punctuation, '\n'
	open_directory(emails_size, caps_size, email_chars, spammer, email_punc,
				   max_newline);
	// Free buffer and file pointers
	free(str);
	fclose(keywords_file);
	fclose(more_keywords_file);
}
