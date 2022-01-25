#include "structures.h"
void verify_email(words *output[], int **emails_size, int **caps_size, int **emails_chars, int **spammer);

void count_word(char *email_name, words *output[], int index, int index_email);

void generate_output(words *output[]);

void open_directory_alloc(words *output[], int **emails_size, int **caps_size, int **emails_chars, int **spammer);

void free_struct(words **output, int **emails_size, int **caps_size, int **emails_chars, int **spammer);

void compute_emails_size(char *email_name, int index_email, int **emails_size, int **caps_size, int **emails_chars, int **spammer);

void generate_score(words **output, int **emails_size, int **caps_size, int **emails_chars, int **spammer);

void open_directory(int **emails_size, int **caps_size, int **emails_chars, int **spammer);

double average_email_size(words **output, int **emails_size);

void count_keywords(words **output, int index);
