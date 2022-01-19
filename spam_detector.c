#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#define MAX_KEYWORDS 10000
int main(void)
{
	words *output;
	verify_email(&output);
	generate_output(&output);
	free_struct(&output);
	return 0;
}