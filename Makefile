
all: test

test:
	gcc -g tests/check_vec.c vec.c unity/unity.c -Iunity -I. -o tests/check_vec

check: test
	./tests/check_vec

clean:
	rm tests/check_vec
