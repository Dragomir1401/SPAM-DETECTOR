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
	free_struct(&output, &emails_size, &caps_size, &email_chars,
				&spammer, &email_punc, &max_newline);
	return 0;
}
