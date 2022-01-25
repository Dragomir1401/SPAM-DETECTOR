#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include <math.h>
#define BUFF_SIZE 1000
#define MAX_SOURCE 100

double keywords_score(words **output, int **emails_size, int mail_index)
{
    double score = 0;
    double avg = average_email_size(output, emails_size);
    for (int i = 0; i < output[0]->nr_words; i++)
        score += (avg / (*emails_size)[mail_index]) * (*output)[i].email_no[mail_index];
    return score;
}

int uppercase(int *caps_size, int *email_chars, int mail_index)
{
    if (caps_size[mail_index] > 1 / 2 * email_chars[mail_index])
        return 0;

    return 1;
}

void generate_score(words **output, int **emails_size, int **caps_size, int **email_chars, double **spammer)
{
    FILE *score_file = fopen("spammers.out", "w");
    if (!score_file)
    {
        printf("Failed to load Spammers.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < output[0]->nr_emails; i++)
    {
        double score = 0;
        score += 30 * uppercase(*caps_size, *email_chars, i);
        score += 10 * keywords_score(output, emails_size, i);
        score += (*spammer)[i];
        if (score > 35)
            fprintf(score_file, "%d\n", 1);
        else
            fprintf(score_file, "%d\n", 0);
    }
    fclose(score_file);
}
