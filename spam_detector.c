#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#define MAX_KEYWORDS 10000
int main(void)
{
	words *output;
	int *emails_size;
	verify_email(&output, &emails_size);
	generate_output(&output);
	generate_score(&output, &emails_size);
	free_struct(&output, &emails_size);
	return 0;
}