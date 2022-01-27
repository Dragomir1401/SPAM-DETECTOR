#pragma once
// Structure for keywords
typedef struct nominal {
	char *keyword;
	int appearances;
	double deviation;
	int nr_words;
	int nr_emails;
	int *email_no;
} words;
// Structure for additional keywords
typedef struct nominal1 {
	int new_appereances;
	int nr_new_words;
	char *more_keywords;
	int *more_email_no;
} new_words;
