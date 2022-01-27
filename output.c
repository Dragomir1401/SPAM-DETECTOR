#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include <ctype.h>
#include <math.h>
#define BUFF_SIZE 1000
#define MAX_SOURCE 100
#define MAX_ADRESS 100
double average(words * *output, int index)
{
	// Function to calculate average apparitions of a keyword in a mail
	double result = 0;
	for (int i = 0; i < output[0]->nr_emails; i++)
		result += (*output)[index].email_no[i];
	return result / output[0]->nr_emails;
}

void compute_deviation(words **output, int index)
{
	// Function which calculates standard deviation for each keyword
	// by the formula
	double sum = 0;
	double avr = average(output, index);
	for (int i = 0; i < output[0]->nr_emails; i++)
		sum += ((*output)[index].email_no[i] - avr) *
			   ((*output)[index].email_no[i] - avr);
	sum /= output[0]->nr_emails;
	sum = sqrt(sum);
	(*output)[index].deviation = sum;
}

void generate_output(words **output)
{
	// Open statistics file
	FILE *statistics_file = fopen("statistics.out", "w");
	if (!statistics_file) {
		printf("Failed to load Statistics.\n");
		exit(EXIT_FAILURE);
	}
	// Generate output for task 1 with the standard deviation of each keyword
	for (int i = 0; i < output[0]->nr_words; i++) {
		fputs((*output)[i].keyword, statistics_file);
		fprintf(statistics_file, " %d", (*output)[i].appearances);
		compute_deviation(output, i);
		fprintf(statistics_file, " %f\n", (*output)[i].deviation);
	}
	// Close statistics file
	fclose(statistics_file);
}

int isspammer(char *sender, char *str)
{
	// Make a copy of the sender email address
	char sender1[MAX_ADRESS];
	for (size_t i = 0; i < strlen(sender); i++)
		sender1[i] = sender[i];
	sender1[strlen(sender)] = '\0';
	// Open spammers file
	char source[MAX_SOURCE] = "data/spammers";
	FILE *spammers_file = fopen(source, "r");
	if (!spammers_file) {
		printf("Failed to load an Spammers text.\n");
		exit(EXIT_FAILURE);
	}
	// Read nr of spammers
	int nr_spammers, found = 0;
	fscanf(spammers_file, "%d", &nr_spammers);
	// Alloc 2 strings for spammer name and score
	char *spammer_name, *spammer_score;
	spammer_name = malloc(MAX_ADRESS);
	spammer_score = malloc(MAX_ADRESS);

	int score;

	for (int i = 0; i < nr_spammers + 1; i++) {
		// Read line by line and check excepting line 1 with nr of spamemers
		fgets(str, BUFF_SIZE, spammers_file);
		if (i) {
			char *token1;
			int nr_token = 0;
			// Get 2 tokens for each element
			// Spammer email and spammer score
			token1 = strtok(str, " ");

			/* walk through other tokens */
			while (token1) {
				if (nr_token == 0) {
					strcpy(spammer_name, token1);
				} else if (nr_token == 1) {
					strcpy(spammer_score, token1);
					spammer_score[strlen(spammer_score) - 1] = '\0';
				}

				nr_token++;
				token1 = strtok(NULL, " ");
			}
			// If we find the sender as a spammer we take
			// consideration of its score
			if (strstr(sender1, spammer_name)) {
				found = 1;
				score = atoi(spammer_score);
			}
		}
	}
	// Free the arrays used
	free(spammer_name);
	free(spammer_score);
	// Close spammer file
	fclose(spammers_file);
	// If we found the sender as spammer we return its score
	if (found)
		return score;
	else
		return 0;
}

void free_struct(words **output, int **emails_size, int **caps_size,
				 int **emails_chars, int **spammer, int **email_punc,
				 int **max_newline, new_words **added)
{
	// Free each array used for measurements
	free(*emails_size);
	free(*caps_size);
	free(*emails_chars);
	free(*spammer);
	free(*email_punc);
	free(*max_newline);
	// Free each array for keyword appereances in each mail
	for (int i = 0; i < output[0]->nr_words; i++) {
		free((*output)[i].keyword);
		free((*output)[i].email_no);
	}
	// Free each array for additional keyword appereances in each mail
	for (int i = 0; i < added[0]->nr_new_words; i++) {
		free((*added)[i].more_keywords);
		free((*added)[i].more_email_no);
	}
	// Free structs
	free(*output);
	free(*added);
}

void compute_emails_size(char *email_name, int index_email, int **emails_size,
						 int **caps_size, int **email_chars, int **spammer,
						 int **email_punc, int **max_newline)
{
	// Open each email by concatenating email name and path
	char source[MAX_SOURCE] = "data/emails/";
	strcat(source, email_name);

	FILE *email_file = fopen(source, "r");
	if (!email_file) {
		printf("Failed to load an Email.\n");
		exit(EXIT_FAILURE);
	}
	// Inititalizing variables for different measurements
	int step = 0, nr_words = 0, nr_caps = 0, nr_chars = 0, nr_punc = 0;
	// Declare and alloc a buffer to read linde by line the email
	char *str;
	str = malloc(BUFF_SIZE);
	if (!str) {
		printf("Cant alloc memory");
		exit(EXIT_FAILURE);
	}
	// Set up variables for getting streak of new lines
	int streak = 0, max = 0;
	while (fgets(str, BUFF_SIZE, email_file)) {
		// Read line by line and coutn steps
		step++;
		char *token;
		// Count new lines streak
		if (!strcmp(str, "\n") && step > 3)
			streak++;
		else
			streak = 0;
		// Get max streak
		if (streak > max) {
			max = streak;
			streak = 0;
		}
		// Count characters and uppercases only for email body
		if (step > 3) {
			for (size_t i = 0; i < strlen(str); i++) {
				if (str[i] != '\n' && str[i] != ' ' && str[i] != '<' &&
					str[i] != '>' && str[i] != ':' && str[i] != ';' &&
					str[i] != '!' && str[i] != '?') {
					nr_chars++;
					if (isupper(str[i]))
						nr_caps++;
				} else if (str[i] != '\n' && str[i] != '-') {
					nr_punc++;
				}
			}
		}
		// Split email word by word
		if (str[0] != '\n')
			token = strtok(str, " ");
		else
			token = NULL;
		// Walk through other words
		while (token) {
			if (step == 3) {
				// If we find the email word on the line with this info
				// We go ahead and check if its a common spammer
				if (strstr(token, "@"))
					(*spammer)[index_email] = isspammer(token, str);
			}
			// Count email body words
			if (step > 3)
				nr_words++;
			token = strtok(NULL, " ");
		}
	}
	// Put the measurements in their correspondent arrays
	(*max_newline)[index_email] = max;
	(*emails_size)[index_email] = nr_words;
	(*caps_size)[index_email] = nr_caps;
	(*email_chars)[index_email] = nr_chars;
	(*email_punc)[index_email] = nr_punc;
	// Free buffer and close file
	free(str);
	fclose(email_file);
}

double average_email_size(words **output, int **emails_size)
{
	// Function which computes average email size in characters
	double avg = 0;
	for (int i = 0; i < output[0]->nr_emails; i++)
		avg += (*emails_size)[i];
	avg /= output[0]->nr_emails;
	return avg;
}
