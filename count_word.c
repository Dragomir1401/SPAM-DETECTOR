#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include <ctype.h>
#define BUFF_SIZE 1000
#define MAX_SOURCE 100

int isupper_string(char *string)
{
    for (size_t i = 0; i < strlen(string); i++)
        if (isupper(string[i]))
            return 1;
    return 0;
}

void tolower_string(char *string)
{
    for (size_t i = 0; i < strlen(string); i++)
        if (isalpha(string[i]))
            string[i] = tolower(string[i]);
}

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
    int step = 0;
    while (fgets(str, BUFF_SIZE, email_file))
    {
        step++;
        char *token;

        /* get the first token */
        token = strtok(str, " ");
        if (isupper_string(token))
            tolower_string(token);
        /* walk through other tokens */
        while (token != NULL)
        {
            if (isupper_string(token))
                tolower_string(token);

            if (strstr(token, (*output)[index].keyword))
                if (step > 3)
                    (*output)[index].appearances++;

            if (strstr(token, "buy") && !strcmp((*output)[index].keyword, "buy"))
                printf("%s\n", token);

            token = strtok(NULL, " ");
        }
    }

    free(str);
    fclose(email_file);
}
