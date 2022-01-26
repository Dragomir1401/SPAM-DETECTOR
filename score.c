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
	int total_keywords = 0;
	int new_keywords = 0;
	double avg = average_email_size(output, emails_size);
	printf("Average email size is:%f\n", avg);
	//if (avg / (*emails_size)[mail_index] < 8) {
	for (int i = 0; i < output[0]->nr_words; i++) {
		if ((*emails_size)[mail_index] > 50)
			score += (avg / (*emails_size)[mail_index]) *
				 (*output)[i].email_no[mail_index];
		score += (avg / (*emails_size)[mail_index]) *
			(*output)[i].more_email_no[mail_index];
		total_keywords += (*output)[i].email_no[mail_index];
		new_keywords += (*output)[i].more_email_no[mail_index];
	}
	// } else {
	//	for (int i = 0; i < output[0]->nr_words; i++) {
	//		score += (*output)[i].email_no[mail_index];
	//		total_keywords += (*output)[i].email_no[mail_index];
	//	}
	// }

	printf("Nr keywords in mail:%d\n", total_keywords);
	printf("Nr of new keywords in mail:%d\n", new_keywords);
	return score;
}

int uppercase(int *caps_size, int *email_chars, int mail_index)
{
	//printf("%d %d\n", caps_size[mail_index], email_chars[mail_index]);
	if (caps_size[mail_index] > (email_chars[mail_index] / 2))
		return 1;

	return 0;
}

void generate_score(words **output, int **emails_size, int **caps_size,
					int **email_chars, int **spammer, int **nr_punc,
					int **max_newline)
{
	FILE *score_file = fopen("prediction.out", "w");
	if (!score_file) {
		printf("Failed to load predictions.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < output[0]->nr_emails; i++) {
		printf("Mail number %d\n", i);
		printf("Spammer score:%d\n", (*spammer)[i]);
		printf("Uppercases:%d\nTotal characters :%d\n",
			   (*caps_size)[i], (*email_chars)[i]);
		printf("Total words in mail:%d\n", (*emails_size)[i]);
		printf("Keywords score:%f\n", keywords_score(output, email_chars, i));
		double score = 0;
		score += 30 * uppercase(*caps_size, *email_chars, i);
		score += 10 * keywords_score(output, email_chars, i);
		score += (*spammer)[i];
		double ratio;
		ratio = (double)(*nr_punc)[i] / (*email_chars)[i];
		printf("Ratio:%f\n", ratio);
		if (ratio > 0.31)
			score += 100 * ratio;
		if ((*max_newline)[i] > 3)
			score += (*max_newline)[i] * 10;
		if (score > 36)
			fprintf(score_file, "%d\n", 1);
		else
			fprintf(score_file, "%d\n", 0);
		printf("Score:%f\n\n", score);
	}
	fclose(score_file);
}
