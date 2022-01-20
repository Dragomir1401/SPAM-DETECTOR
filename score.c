#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include <math.h>
#define BUFF_SIZE 1000
#define MAX_SOURCE 100

// double keywords_score(words **output, int mail_index)
// {
// }

void generate_score(words **output, int **emails_size)
{
    FILE *score_file = fopen("spammers.out", "w");
    if (!score_file)
    {
        printf("Failed to load Spammers.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < output[0]->nr_emails; i++)
        fprintf(score_file, "%d\n", (*emails_size)[i]);
    fclose(score_file);
}