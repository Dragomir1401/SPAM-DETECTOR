#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"

#define BUFF_SIZE 1000
#define MAX_SOURCE 100

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
        fprintf(statistics_file, " %d\n", (*output)[i].appearances);
    }
    fclose(statistics_file);
}

void free_struct(words **output)
{
    for (int i = 0; i < output[0]->nr_words; i++)
    {
        free((*output)[i].keyword);
    }
    free(*output);
}