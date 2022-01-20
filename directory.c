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
void open_directory(words **output, int index, int **emails_size)
{
	int number_files = 0;
	struct dirent *res;
	struct stat sb;
	const char *path = "/home/student/Documents/BALIZA/data/emails/";

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		DIR *folder = opendir(path);

		if (access(path, F_OK) != -1)
		{
			if (folder)
			{
				while ((res = readdir(folder)))
				{
					if (strcmp(res->d_name, ".") && strcmp(res->d_name, ".."))
					{
						//printf("%d---%s\n", number_files, res->d_name);
						//verify_email(res->d_name, output);
						//count_word(res->d_name, output, index);
						number_files++;
					}
				}

				closedir(folder);
			}
			else
			{
				perror("Could not open the directory");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		printf("The %s it cannot be opened or is not a directory\n", path);
		exit(EXIT_FAILURE);
	}

	(*output)[0].nr_emails = number_files;
	(*output)[index].email_no = malloc((*output)[0].nr_emails * sizeof(int));
	*emails_size = malloc((*output)[0].nr_emails * sizeof(int));

	int index_email = 0;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		DIR *folder = opendir(path);

		if (access(path, F_OK) != -1)
		{
			if (folder)
			{
				while ((res = readdir(folder)))
				{
					if (strcmp(res->d_name, ".") && strcmp(res->d_name, ".."))
					{
						//printf("%d---%s\n", number_files, res->d_name);
						//verify_email(res->d_name, output);
						(*output)[index].email_no[index_email] = 0;
						count_word(res->d_name, output, index, index_email);
						compute_emails_size(res->d_name, index_email, emails_size);
						index_email++;
					}
				}

				closedir(folder);
			}
			else
			{
				perror("Could not open the directory");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		printf("The %s it cannot be opened or is not a directory\n", path);
		exit(EXIT_FAILURE);
	}
}
