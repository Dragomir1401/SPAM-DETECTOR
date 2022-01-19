#Copyright Dragomir Andrei-Mihai
#compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -g -lm

# define targets
TARGET=spam_detector

build: $(TARGET)

spam_detector: spam_detector.o directory.o wordlist.o count_word.o output.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $^

pack:
	zip -FSr 312CA_DragomirAndrei_SpamDetector.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean