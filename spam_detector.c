#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
int main(void)
{
	// Declare structures to store initial keywords and added keywords
	words *output;
	new_words *added;
	// Declare arrays needed for keeping track of different measurements
	int *emails_size, *caps_size, *email_chars, *email_punc;
	int *spammer, *max_newline;
	// Call function that sets up output
	verify_email(&output, &emails_size, &caps_size, &email_chars,
				 &spammer, &email_punc, &max_newline, &added);
	// Call function that generates output for task 1
	generate_output(&output);
	// Call function that generates score for task 2
	generate_score(&output, &caps_size, &email_chars,
				   &spammer, &email_punc, &max_newline, &added);
	// Call global free function
	free_struct(&output, &emails_size, &caps_size, &email_chars,
				&spammer, &email_punc, &max_newline, &added);
	return 0;
}
