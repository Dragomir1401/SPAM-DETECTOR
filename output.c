#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include <math.h>
#define BUFF_SIZE 1000
#define MAX_SOURCE 100

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

void free_struct(words **output, int **emails_size)
{
	for (int i = 0; i < output[0]->nr_words; i++)
	{
		free((*output)[i].keyword);
		free((*output)[i].email_no);
	}
	for (int i = 0; i < output[0]->nr_emails; i++)
		free((*emails_size)[i]);
	free(*output);
}

void compute_emails_size(char *email_name, int index_email, int **emails_size)
{
	char source[MAX_SOURCE] = "/home/student/Documents/BALIZA/data/emails/";
	strcat(source, email_name);

	FILE *email_file = fopen(source, "r");
	if (!email_file)
	{
		printf("Failed to load an Email.\n");
		exit(EXIT_FAILURE);
	}

	int step = 0, nr_words = 0;
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
			if (step > 3)
			{
				nr_words++;
			}
			token = strtok(NULL, " ");
		}
	}

	(*emails_size)[index_email] = nr_words;
	free(str);
	fclose(email_file);
}