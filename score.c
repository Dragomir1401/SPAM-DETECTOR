#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include <math.h>
#define BUFF_SIZE 1000
#define MAX_SOURCE 100
#define MAX_BODY 17500
#define MIN_BODY 75
double keywords_score(words * *output, int **emails_size, int mail_index,
					  new_words * *added)
{
	double score = 0;
	// Calculate average email size in characters
	double avg = average_email_size(output, emails_size);
	// Add each keyword appereance score to the to be returned score
	for (int i = 0; i < output[0]->nr_words; i++)
		score += (avg / (*emails_size)[mail_index]) *
				 (*output)[i].email_no[mail_index];
	// Add each additional keyword appereance score to the to be returned score
	for (int i = 0; i < added[0]->nr_new_words; i++)
		score += (avg / (*emails_size)[mail_index]) *
				(*added)[i].more_email_no[mail_index];

	return score;
}

int uppercase(int *caps_size, int *email_chars, int mail_index)
{
	// Verify if a mail has more than half characters uppercases
	if (caps_size[mail_index] > (email_chars[mail_index] / 2))
		return 1;
	return 0;
}

void generate_score(words **output, int **caps_size,
					int **email_chars, int **spammer, int **nr_punc,
					int **max_newline, new_words **added)
{
	// Open predictions file
	FILE *score_file = fopen("prediction.out", "w");
	if (!score_file) {
		printf("Failed to load predictions.\n");
		exit(EXIT_FAILURE);
	}
	// Iterate through each email info
	for (int i = 0; i < output[0]->nr_emails; i++) {
		double score = 0;
		// Add uppercase score
		score += 30 * uppercase(*caps_size, *email_chars, i);
		// Add keywords score
		score += 10 * keywords_score(output, email_chars, i, added);
		// Add spammer score if exits
		score += (*spammer)[i];
		// Calculate ratio of punctuation to total characters
		double ratio;
		ratio = (double)(*nr_punc)[i] / (*email_chars)[i];
		if (ratio > 0.31)
			score += 100 * ratio;
		// Modify score if we find a streak on newlines bigger than 3
		if ((*max_newline)[i] > 3)
			score += (*max_newline)[i] * 10;
		// If the score gets out of bound or is too long or short is spam
		if (score > 36 && (*email_chars)[i] > MIN_BODY &&
			(*email_chars)[i] < MAX_BODY)
			fprintf(score_file, "%d\n", 1);
		else
			fprintf(score_file, "%d\n", 0);
	}
	// Close file
	fclose(score_file);
}

