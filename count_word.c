#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include <ctype.h>
#define BUFF_SIZE 1000
#define MAX_SOURCE 100

int isupper_string(char *string)
{
	// Function to verify a string has at least one uppercase
	for (size_t i = 0; i < strlen(string); i++)
		if (isupper(string[i]))
			return 1;
	return 0;
}

void tolower_string(char *string)
{
	// Functions which turns a string lowercase
	for (size_t i = 0; i < strlen(string); i++)
		if (isalpha(string[i]))
			string[i] = tolower(string[i]);
}

void count_word(char *email_name, words **output, int index, int index_email)
{
	// Open email with the given name
	char source[MAX_SOURCE] = "data/emails/";
	strcat(source, email_name);

	FILE *email_file = fopen(source, "r");
	if (!email_file) {
		printf("Failed to load an Email.\n");
		exit(EXIT_FAILURE);
	}
	// Alloc a buffer
	char *str;
	str = malloc(BUFF_SIZE);
	if (!str) {
		printf("Cant alloc memory");
		exit(EXIT_FAILURE);
	}
	// Read email line by line
	int step = 0;
	while (fgets(str, BUFF_SIZE, email_file)) {
		// Count steps
		step++;
		char *token;
		// Split each email line in words
		token = strtok(str, " ");
		// Make word lowercase
		if (isupper_string(token))
			tolower_string(token);
		// Get all the words
		while (token) {
			// Make word lowercase
			if (isupper_string(token))
				tolower_string(token);
			// If we find an appereance of the keyword we count it
			char *p = strstr(token, (*output)[index].keyword);
			if (step > 3)
				// Use a pointer to count all appereances of each keyword
				// by moving strlen(keyword) chars in the token each time
				while (p) {
					(*output)[index].appearances++;
					(*output)[index].email_no[index_email]++;

					p += strlen((*output)[index].keyword);
					p = strstr(p, (*output)[index].keyword);
				}
			token = strtok(NULL, " ");
		}
	}
	// Free buffer and close file
	free(str);
	fclose(email_file);
}

void count_more_words(char *email_name, int index, int index_email,
					  new_words **added)
{
	// Open email with the given name
	char source[MAX_SOURCE] = "data/emails/";
	strcat(source, email_name);

	FILE *email_file = fopen(source, "r");
	if (!email_file) {
		printf("Failed to load an Email.\n");
		exit(EXIT_FAILURE);
	}
	// Alloc a buffer
	char *str;
	str = malloc(BUFF_SIZE);
	if (!str) {
		printf("Cant alloc memory");
		exit(EXIT_FAILURE);
	}
	// Read email line by line
	int step = 0;
	while (fgets(str, BUFF_SIZE, email_file)) {
		// Count steps
		step++;
		char *token;

		// Split each email line in words
		token = strtok(str, " ");
		// Make string lowercase
		if (isupper_string(token))
			tolower_string(token);
		// Walk through all words
		while (token) {
			// Make string lowercase
			if (isupper_string(token))
				tolower_string(token);
			// If we find an appereance of the additional keyword we count it
			char *p = strstr(token, (*added)[index].more_keywords);
			if (step > 3)
				// Use a pointer to count all appereances of each keyword
				// by moving strlen(keyword) chars in the token each time
				while (p) {
					(*added)[index].more_email_no[index_email]++;
					(*added)[index].new_appereances++;
					p += strlen((*added)[index].more_keywords);
					p = strstr(p, (*added)[index].more_keywords);
				}
			token = strtok(NULL, " ");
		}
	}
	// Free buffer and close file
	free(str);
	fclose(email_file);
}
