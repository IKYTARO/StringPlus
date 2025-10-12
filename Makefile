CC      = gcc
CFLAGS  = -std=c11 #-Wall -Werror -Wextra
TFLAGS  = -lcheck -lm -lsubunit
ARCHIVE = ar
ARFLAGS = rcs

SOURCES = my_string.c my_sscanf.c my_sprintf.c utils.c specifier_parser.c specifier_handler.c
OBJECTS = $(SOURCES:.c=.o)
TESTSRC = ./tests/*.c

TEST_TARGET = all_tests
TESTING_LOG = test_report.log

STATIC_LIB = my_string.a

all: test

$(STATIC_LIB):
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(ARCHIVE) $(ARFLAGS) $@ $(OBJECTS)

test: $(STATIC_LIB)
	gcc $(CFLAGS) $(TESTSRC) $(TFLAGS) -o $(TEST_TARGET) $(STATIC_LIB)
	./$(TEST_TARGET) > $(TESTING_LOG)

clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf $(TEST_TARGET)
	rm -rf $(TESTING_LOG)

rebuild:

format:
	clang-format -i *.c *.h 

check-format:
	clang-format -n *.c *.h 

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

leaks:

valgrind: