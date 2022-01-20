#include "structures.h"
void verify_email(words *output[], int **emails_size);
void count_word(char *email_name, words *output[], int index, int index_email);
void generate_output(words *output[]);
void open_directory(words *output[], int index, int **emails_size);
void free_struct(words **output, int **emails_size);
void compute_emails_size(char *email_name, int index_email, int **emails_size);
void generate_score(words **output, int **emails_size);
