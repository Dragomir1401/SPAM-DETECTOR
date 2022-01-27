#include "structures.h"
void verify_email(words * output[], int **emails_size, int **caps_size,
				  int **emails_chars, int **spammer, int **email_punc,
				  int **max_newline, new_words * *added);

void count_word(char *email_name, words * output[], int index,
				int index_email);

void generate_output(words * output[]);

void open_directory_alloc(words * output[], int **emails_size,
						  int **caps_size, int **emails_chars, int **spammer,
						  int **email_punc, int **max_newline);

void free_struct(words **output, int **emails_size, int **caps_size,
				 int **emails_chars, int **spammer, int **email_punc,
				 int **max_newline, new_words **added);

void compute_emails_size(char *email_name, int index_email, int **emails_size,
						 int **caps_size, int **emails_chars, int **spammer,
						 int **email_punc, int **max_newline);

void generate_score(words **output, int **caps_size,
					int **emails_chars, int **spammer, int **email_punc,
					int **max_newline, new_words **added);

void open_directory(int **emails_size, int **caps_size, int **emails_chars,
					int **spammer, int **email_punc, int **max_newline);

double average_email_size(words **output, int **emails_size);

void count_keywords(words **output, int index);

void count_more_words(char *email_name, int index,
					  int index_email, new_words **added);

void count_more_keywords(new_words **added, int index, words **output);
