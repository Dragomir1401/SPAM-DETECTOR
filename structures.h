#pragma once
typedef struct nominal {
	char *keyword;
	int appearances;
	double deviation;
	int new_appereances;
	int nr_words;
	int nr_emails;
	int *email_no;
	char *more_keywords;
	int *more_email_no;
} words;
