#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <features.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "structures.h"
#include "headers.h"
#define _GNU_SOURCE
#define _BSD_SOURCE

void open_directory_alloc(words **output, int **emails_size, int **caps_size,
						  int **email_chars, int **spammer, int **email_punc,
						  int **max_newline)
{
	int number_files = 0;
	struct dirent *res;
	struct stat sb;
	const char *path = "data/emails/";
	// Open each file in emails directory one by one in randomized order
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		DIR *folder = opendir(path);

		if (access(path, F_OK) != -1) {
			if (folder) {
				while ((res = readdir(folder))) {
					if (strcmp(res->d_name, ".") && strcmp(res->d_name, ".."))
						// Count number of files in directory emails
						number_files++;
				}

				closedir(folder);
			} else {
				perror("Could not open the directory");
				exit(EXIT_FAILURE);
			}
		}
	} else {
		printf("The %s it cannot be opened or is not a directory\n", path);
		exit(EXIT_FAILURE);
	}
	// Alloc each array used for measurements
	(*output)[0].nr_emails = number_files;
	*emails_size = malloc((*output)[0].nr_emails * sizeof(int));
	*caps_size = malloc((*output)[0].nr_emails * sizeof(int));
	*email_chars = malloc((*output)[0].nr_emails * sizeof(int));
	*spammer = malloc((*output)[0].nr_emails * sizeof(int));
	*email_punc = malloc((*output)[0].nr_emails * sizeof(int));
	*max_newline = malloc((*output)[0].nr_emails * sizeof(int));
}

void open_directory(int **emails_size, int **caps_size, int **email_chars,
					int **spammer, int **email_punc, int **max_newline)
{
	struct dirent *res;
	struct stat sb;
	const char *path = "data/emails/";
	// Open each file in emails directory one by one in randomized order
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		DIR *folder = opendir(path);

		if (access(path, F_OK) != -1) {
			if (folder) {
				while ((res = readdir(folder))) {
					if (strcmp(res->d_name, ".") && strcmp(res->d_name, "..")) {
						// Calculate each email size with different measurements
						compute_emails_size(res->d_name, atoi(res->d_name),
											emails_size, caps_size,
											email_chars, spammer, email_punc,
											max_newline);
					}
				}

				closedir(folder);
			} else {
				perror("Could not open the directory");
				exit(EXIT_FAILURE);
			}
		}
	} else {
		printf("The %s it cannot be opened or is not a directory\n", path);
		exit(EXIT_FAILURE);
	}
}

void count_keywords(words **output, int index)
{
	struct dirent *res;
	struct stat sb;
	const char *path = "data/emails/";
	// Alloc memory for each array of emails in struct
	// output[index] is an array for keywords while email_no[index_email]
	// states how many of the selected keyword are in the email with the index
	// index_email
	(*output)[index].email_no = malloc((*output)[0].nr_emails * sizeof(int));
	// Open each file in emails directory one by one in randomized order
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		DIR *folder = opendir(path);

		if (access(path, F_OK) != -1) {
			if (folder) {
				while ((res = readdir(folder))) {
					if (strcmp(res->d_name, ".") && strcmp(res->d_name, "..")) {
						// Initialise array of emails
						(*output)[index].email_no[atoi(res->d_name)] = 0;
						// Count each keyword apparition in each mail
						count_word(res->d_name, output, index,
								   atoi(res->d_name));
					}
				}

				closedir(folder);
			} else {
				perror("Could not open the directory");
				exit(EXIT_FAILURE);
			}
		}
	} else {
		printf("The %s it cannot be opened or is not a directory\n", path);
		exit(EXIT_FAILURE);
	}
}

void count_more_keywords(new_words **added, int index, words **output)
{
	int index_email = 0;
	struct dirent *res;
	struct stat sb;
	const char *path = "data/emails/";
	// Alloc memory for each array of emails in struct
	// added[index] is an array for keywords while more_email_no[index_email]
	// states how many of the selected additional keyword are in the email
	// with the index index_email
	(*added)[index].more_email_no = malloc((*output)[0].nr_emails *
										    sizeof(int));
	// Open each file in emails directory one by one in randomized order
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		DIR *folder = opendir(path);

		if (access(path, F_OK) != -1) {
			if (folder) {
				while ((res = readdir(folder))) {
					if (strcmp(res->d_name, ".") && strcmp(res->d_name, "..")) {
						// Initialise array of emails
						(*added)[index].more_email_no[atoi(res->d_name)] = 0;
						// Count each additional keyword apparition in each mail
						count_more_words(res->d_name, index,
										 atoi(res->d_name), added);
						index_email++;
					}
				}

				closedir(folder);
			} else {
				perror("Could not open the directory");
				exit(EXIT_FAILURE);
			}
		}
	} else {
		printf("The %s it cannot be opened or is not a directory\n", path);
		exit(EXIT_FAILURE);
	}
}

