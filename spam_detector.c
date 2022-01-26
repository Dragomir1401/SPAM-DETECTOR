#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
int main(void)
{
	words *output;
	int *emails_size, *caps_size, *email_chars;
	int *spammer;
	verify_email(&output, &emails_size, &caps_size, &email_chars, &spammer);
	generate_output(&output);
	generate_score(&output, &emails_size, &caps_size, &email_chars, &spammer);
	free_struct(&output, &emails_size, &caps_size, &email_chars, &spammer);
	return 0;
}