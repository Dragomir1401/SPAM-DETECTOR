#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"

#define BUFF_SIZE 1000
#define MAX_SOURCE 100
void count_word(char *email_name, words **output, int index)
{
    char source[MAX_SOURCE] = "/home/student/Documents/BALIZA/data/emails/";
    strcat(source, email_name);

    FILE *email_file = fopen(source, "r");
    if (!email_file)
    {
        printf("Failed to load an Email.\n");
        exit(EXIT_FAILURE);
    }

    char *str;
    str = malloc(BUFF_SIZE);
    if (str == NULL)
    {
        printf("Cant alloc memory");
        exit(EXIT_FAILURE);
    }

    while (fgets(str, BUFF_SIZE, email_file))
    {
        char *token;

        /* get the first token */
        token = strtok(str, " ");

        /* walk through other tokens */
        while (token != NULL)
        {
            if (strstr(token, (*output)[index].keyword))
                (*output)[index].appearances++;
            if (strstr(token, "buy"))
                printf("%s\n", token);
            token = strtok(NULL, " ");
        }
    }

    free(str);
    fclose(email_file);
}
