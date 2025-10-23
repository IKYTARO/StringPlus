#include "test.h"

int main(void) {
    Suite *suite_array[] = {suite_insert(),   suite_memchr(),
                            suite_memcmp(),   suite_memcpy(),
                            suite_memset(),   suite_sprintf(),
                            suite_sscanf(),   suite_strchr(),
                            suite_strcspn(),  suite_strerror(),
                            suite_strlen(),   suite_strncat(),
                            suite_strncmp(),  suite_strncpy(),
                            suite_strpbrk(),  suite_strrchr(),
                            suite_strstr(),   suite_strtok(),
                            suite_to_lower(), suite_to_upper(),
                            suite_trim(),     NULL};

    for (int i = 0; suite_array[i] != NULL; i++) {
        SRunner *runner = srunner_create(suite_array[i]);
        srunner_set_fork_status(runner, CK_NOFORK);
        srunner_run_all(runner, CK_NORMAL);
        srunner_free(runner);
    }

    return 0;
}