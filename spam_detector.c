#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
int main(void)
{
	words *output;
	int *emails_size, *caps_size, *email_chars, *email_punc;
	int *spammer, *max_newline;
	verify_email(&output, &emails_size, &caps_size, &email_chars,
				 &spammer, &email_punc, &max_newline);
	generate_output(&output);
	generate_score(&output, &emails_size, &caps_size, &email_chars,
				   &spammer, &email_punc, &max_newline);
	for (int i = 0; i < output[0].nr_words; i++)
		printf("Total appereances for keyword %s: %d\n",
			   output[i].more_keywords, output[i].new_appereances);
	printf("\n");
	for (int i = 0; i < output[0].nr_words; i++)
		printf("Total appereances for keyword %s: %d\n",
			   output[i].keyword, output[i].appearances);
	free_struct(&output, &emails_size, &caps_size, &email_chars,
				&spammer, &email_punc, &max_newline);
	return 0;
}
