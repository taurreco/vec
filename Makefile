
CC = gcc

CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -std=c99
CFLAGS += -g

all: test

test:
	$(CC) $(CFLAGS) test.c vec.c unity.c -o test

check: test
	./test

clean:
	rm test
