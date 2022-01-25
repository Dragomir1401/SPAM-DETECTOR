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
double average(words **output, int index)
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
		sum += ((*output)[index].email_no[i] - avr) * ((*output)[index].email_no[i] - avr);
	sum /= output[0]->nr_emails;
	sum = sqrt(sum);
	(*output)[index].deviation = sum;
}

void generate_output(words **output)
{
	FILE *statistics_file = fopen("statistics.out", "w");
	if (!statistics_file)
	{
		printf("Failed to load Statistics.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < output[0]->nr_words; i++)
	{
		fputs((*output)[i].keyword, statistics_file);
		fprintf(statistics_file, " %d", (*output)[i].appearances);
		compute_deviation(output, i);
		fprintf(statistics_file, " %f\n", (*output)[i].deviation);
	}
	fclose(statistics_file);
}

double isspammer(char *sender)
{
	char source[MAX_SOURCE] = "/home/student/Documents/BALIZA/data/spammers";
	FILE *spammers_file = fopen(source, "r");
	if (!spammers_file)
	{
		printf("Failed to load an Spammers text.\n");
		exit(EXIT_FAILURE);
	}

	int nr_spammers, found = 0;
	fscanf(spammers_file, "%d", &nr_spammers);

	char *spammer_name, *spammer_score;
	spammer_name = malloc(MAX_ADRESS);
	spammer_score = malloc(MAX_ADRESS);

	double score;

	char *strr;
	strr = malloc(BUFF_SIZE);
	if (!strr)
	{
		printf("Cant alloc memory");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < nr_spammers; i++)
	{
		while (fgets(strr, BUFF_SIZE, spammers_file))
		{
			char *token;
			int nr_token = 0;
			/* get the first token */
			token = strtok(strr, " ");

			/* walk through other tokens */
			while (token)
			{
				if (nr_token == 0)
					strcpy(spammer_name, token);
				else if (nr_token == 1)
					strcpy(spammer_score, token);
				token = strtok(NULL, " ");
				nr_token++;
			}
		}

		score = atoi(spammer_score);

		if (strstr(sender, spammer_name))
		{
			found = 1;
			score = atoi(spammer_score);
		}
	}

	free(strr);
	free(spammer_name);
	free(spammer_score);
	if (found)
		return score;
	else
		return 0;
}
void free_struct(words **output, int *emails_size, int *caps_size, int *emails_chars, int *spammer)
{
	free(emails_size);
	free(caps_size);
	free(emails_chars);
	free(spammer);

	for (int i = 0; i < output[0]->nr_words; i++)
	{
		free((*output)[i].keyword);
		free((*output)[i].email_no);
	}
	free(*output);
}

void compute_emails_size(char *email_name, int index_email, int **emails_size, int **caps_size, int **email_chars, double **spammer)
{
	char source[MAX_SOURCE] = "/home/student/Documents/BALIZA/data/emails/";
	strcat(source, email_name);

	FILE *email_file = fopen(source, "r");
	if (!email_file)
	{
		printf("Failed to load an Email.\n");
		exit(EXIT_FAILURE);
	}

	int step = 0, nr_words = 0, nr_caps = 0, nr_chars = 0;
	char *str;
	str = malloc(BUFF_SIZE);
	if (!str)
	{
		printf("Cant alloc memory");
		exit(EXIT_FAILURE);
	}

	while (fgets(str, BUFF_SIZE, email_file))
	{
		step++;
		char *token;

		/* get the first token */
		token = strtok(str, " ");
		/* walk through other tokens */
		while (token)
		{
			if (step == 3)
			{
				if (strstr(token, "@"))
					(*spammer)[index_email] = isspammer(token);
			}
			if (step > 3)
			{
				for (size_t i = 0; i < strlen(token); i++)
				{
					if (isupper(token[i]))
						nr_caps++;
					nr_chars++;
				}
				nr_words++;
			}
			token = strtok(NULL, " ");
		}
	}

	(*emails_size)[index_email] = nr_words;
	(*caps_size)[index_email] = nr_caps;
	(*email_chars)[index_email] = nr_chars;
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