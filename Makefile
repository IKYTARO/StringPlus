CC     = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all:

clean:

rebuild:

format:
	clang-format -i *.c *.h 

check-format:
	clang-format -n *.c *.h 

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

leaks:

valgrind: