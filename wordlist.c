#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#define BUFF_SIZE 50

void debug(words **output, int i)
{
	printf("%d~~%s %d\n", i, (*output)[i].keyword, (*output)[i].appearances);
}

void verify_email(words **output, int **emails_size)
{
	FILE *keywords_file = fopen("/home/student/Documents/BALIZA/data/keywords", "r");
	if (!keywords_file)
	{
		printf("Failed to load Keywords.\n");
		exit(EXIT_FAILURE);
	}
	char *str;
	str = malloc(BUFF_SIZE * sizeof(char));
	if (!str)
	{
		printf("Cant alloc memory");
		exit(EXIT_FAILURE);
	}
	int nr_keywords;

	fscanf(keywords_file, "%d\n", &nr_keywords);

	(*output) = malloc(nr_keywords * sizeof(words));
	if ((*output) == NULL)
	{
		printf("Cant alloc memory");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < nr_keywords; i++)
	{
		fgets(str, BUFF_SIZE, keywords_file);
		if (i != nr_keywords - 1)
			str[strlen(str) - 1] = '\0';

		(*output)[i].keyword = malloc(BUFF_SIZE * sizeof(char));
		if (!((*output)[i].keyword))
		{
			printf("Cant alloc memory\n");
			free(*output);
			exit(EXIT_FAILURE);
		}
		strcpy((*output)[i].keyword, str);

		(*output)[i].appearances = 0;
		(*output)[i].deviation = 0;
		(*output)[i].nr_words = nr_keywords;

		//debug(output, i);
	}

	for (int i = 0; i < nr_keywords; i++)
	{
		open_directory(output, i, emails_size);
	}
	free(str);
	fclose(keywords_file);
}
