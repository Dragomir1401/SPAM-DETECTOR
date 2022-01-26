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
	double result = 0;
	for (int i = 0; i < output[0]->nr_emails; i++)
		result += (*output)[index].email_no[i];
	return result / output[0]->nr_emails;
}

void compute_deviation(words **output, int index)
{
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
	FILE *statistics_file = fopen("statistics.out", "w");
	if (!statistics_file) {
		printf("Failed to load Statistics.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < output[0]->nr_words; i++) {
		fputs((*output)[i].keyword, statistics_file);
		fprintf(statistics_file, " %d", (*output)[i].appearances);
		compute_deviation(output, i);
		fprintf(statistics_file, " %f\n", (*output)[i].deviation);
	}
	fclose(statistics_file);
}

int isspammer(char *sender, char *str)
{
	//printf("%s\n", sender);
	char sender1[MAX_ADRESS];
	for (size_t i = 0; i < strlen(sender); i++)
		sender1[i] = sender[i];
	sender1[strlen(sender)] = '\0';

	char source[MAX_SOURCE] = "data/spammers";
	FILE *spammers_file = fopen(source, "r");
	if (!spammers_file) {
		printf("Failed to load an Spammers text.\n");
		exit(EXIT_FAILURE);
	}

	int nr_spammers, found = 0;
	fscanf(spammers_file, "%d", &nr_spammers);

	char *spammer_name, *spammer_score;
	spammer_name = malloc(MAX_ADRESS);
	spammer_score = malloc(MAX_ADRESS);

	int score;

	// char *str;
	// str = malloc(BUFF_SIZE);
	// if (!str)
	// {
	//	printf("Cant alloc memory");
	//	exit(EXIT_FAILURE);
	// }

	for (int i = 0; i < nr_spammers + 1; i++) {
		fgets(str, BUFF_SIZE, spammers_file);
		//printf("%s", str);
		//printf("%s", str);
		//printf("%s\n", str);
		if (i) {
			char *token1;
			int nr_token = 0;
			/* get the first token */
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
			//printf("%s\n", sender1);
			//printf("%s~~%s\n", spammer_name, spammer_score);
			if (strstr(sender1, spammer_name)) {
				found = 1;
				score = atoi(spammer_score);
			}
		}
	}

	free(spammer_name);
	free(spammer_score);

	fclose(spammers_file);
	if (found)
		return score;
	else
		return 0;
}

void free_struct(words **output, int **emails_size, int **caps_size,
				 int **emails_chars, int **spammer, int **email_punc,
				 int **max_newline)
{
	free(*emails_size);
	free(*caps_size);
	free(*emails_chars);
	free(*spammer);
	free(*email_punc);
	free(*max_newline);
	for (int i = 0; i < output[0]->nr_words; i++) {
		free((*output)[i].keyword);
		free((*output)[i].email_no);
		free((*output)[i].more_keywords);
		free((*output)[i].more_email_no);
	}
	free(*output);
}

void compute_emails_size(char *email_name, int index_email, int **emails_size,
						 int **caps_size, int **email_chars, int **spammer,
						 int **email_punc, int **max_newline)
{
	char source[MAX_SOURCE] = "data/emails/";
	strcat(source, email_name);

	//printf("%d\n", index_email);

	FILE *email_file = fopen(source, "r");
	if (!email_file) {
		printf("Failed to load an Email.\n");
		exit(EXIT_FAILURE);
	}

	int step = 0, nr_words = 0, nr_caps = 0, nr_chars = 0, nr_punc = 0;
	char *str;
	str = malloc(BUFF_SIZE);
	if (!str) {
		printf("Cant alloc memory");
		exit(EXIT_FAILURE);
	}

	int streak = 0, max = 0;
	while (fgets(str, BUFF_SIZE, email_file)) {
		step++;
		char *token;
		if (!strcmp(str, "\n") && step > 3)
			streak++;
		else
			streak = 0;
		if (streak > max) {
			max = streak;
			streak = 0;
		}

		if (step > 3) {
			for (size_t i = 0; i < strlen(str); i++) {
				if (str[i] != '\n' && str[i] != ' ' && str[i] != '<' &&
					str[i] != '>' && str[i] != ':' && str[i] != ';' &&
					str[i] != '!' && str[i] != '?') {
					nr_chars++;
					if (isupper(str[i])) {
						// if (!strcmp(email_name, "1"))
						//	printf("%c ", str[i]);
						nr_caps++;
					}
				} else if (str[i] != '\n') {
					nr_punc++;
				}
			}
		}
		// if (!strcmp(email_name, "0"))
		// {
		//	printf("%d\n", step);
		// }
		/* get the first token */
		if (str[0] != '\n')
			token = strtok(str, " ");
		else
			token = NULL;
		/* walk through other tokens */
		while (token) {
			if (step == 3) {
				if (strstr(token, "@"))
					(*spammer)[index_email] = isspammer(token, str);
			}
			if (step > 3)
				nr_words++;
			token = strtok(NULL, " ");
		}
	}

	(*max_newline)[index_email] = max;
	(*emails_size)[index_email] = nr_words;
	(*caps_size)[index_email] = nr_caps;
	(*email_chars)[index_email] = nr_chars;
	(*email_punc)[index_email] = nr_punc;
	free(str);
	fclose(email_file);
}

double average_email_size(words **output, int **emails_size)
{
	double avg = 0;
	for (int i = 0; i < output[0]->nr_emails; i++)
		avg += (*emails_size)[i];
	avg /= output[0]->nr_emails;
	return avg;
}
