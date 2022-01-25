#include "structures.h"
void verify_email(words *output[], int **emails_size, int **caps_size, int **emails_chars, double **spammer);

void count_word(char *email_name, words *output[], int index, int index_email);

void generate_output(words *output[]);

void open_directory_alloc(words *output[], int **emails_size, int **caps_size, int **emails_chars, double **spammer);

void free_struct(words **output, int **emails_size, int **caps_size, int **emails_chars, double **spammer);

void compute_emails_size(char *email_name, int index_email, int **emails_size, int **caps_size, int **emails_chars, double **spammer);

void generate_score(words **output, int **emails_size, int **caps_size, int **emails_chars, double **spammer);

void open_directory(words **output, int index, int **emails_size, int **caps_size, int **emails_chars, double **spammer);

double average_email_size(words **output, int **emails_size);
