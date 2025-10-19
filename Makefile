COMPILER    = gcc
C_FLAGS     = -std=c11#-Wall -Werror -Wextra
GCOV_FLAGS  = -fprofile-arcs -ftest-coverage
CHECK_FLAGS = -lcheck -lm -lsubunit -lpthread
ARCHIVER    = ar
ARCH_FLAGS  = rcs

OBJ_DIR   = object_files
COV_DIR   = coverage_report
TEST_DIR  = tests
UTILS_DIR = utils

SOURCES = $(wildcard *.c $(UTILS_DIR)/*.c)
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.c=.o)))
TESTSRC = $(wildcard $(TEST_DIR)/*.c)

TEST_TARGET = run_tests
TESTING_LOG = test_report.log

STATIC_LIB = my_string.a

$(OBJ_DIR)/%.o: %.c
	$(shell mkdir -p $(OBJ_DIR))
	$(COMPILER) $(C_FLAGS) $(GCOV_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: utils/%.c
	$(shell mkdir -p $(OBJ_DIR))
	$(COMPILER) $(C_FLAGS) $(GCOV_FLAGS) -c $< -o $@

$(STATIC_LIB): $(OBJECTS)
	$(ARCHIVER) $(ARCH_FLAGS) $@ $(OBJECTS) 
	ranlib $(STATIC_LIB)

$(TEST_TARGET): $(STATIC_LIB)
	$(COMPILER) $(C_FLAGS) $(GCOV_FLAGS) $(TESTSRC) $(CHECK_FLAGS) -o $(TEST_TARGET) $(STATIC_LIB)

library: $(STATIC_LIB)

test: $(TEST_TARGET)
	./$(TEST_TARGET) > $(TESTING_LOG)

gcov_report: $(TEST_TARGET)
	$(shell mkdir -p $(COV_DIR))
	./$(TEST_TARGET)
	gcovr -r . --html --html-details --output $(COV_DIR)/coverage_report.html --exclude $(TEST_DIR) --exclude $(UTILS_DIR) --print-summary --branches
	gcovr -r . --exclude $(TEST_DIR) --exclude $(UTILS_DIR) > $(TESTING_LOG)

view-report: gcov_report
	open $(COV_DIR)/coverage_report.html

clean:
	rm -rf $(STATIC_LIB)
	rm -rf $(OBJ_DIR)
	rm -rf $(COV_DIR)
	rm -rf $(TEST_TARGET)
	rm -rf $(TESTING_LOG)
	rm -rf *.gcno
	rm -rf *.gcda

rebuild:

format:
	clang-format -i *.c *.h $(TEST_DIR)/test.h $(TEST_DIR)/test.c

check-format:
	clang-format -n *.c *.h $(TEST_DIR)/test.h $(TEST_DIR)/test.c 

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

leaks:

valgrind: