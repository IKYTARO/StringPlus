#include "test.h"

int main(void) {
    Suite *suite_array[] = {suite_strlen(), suite_strncmp(), suite_strncpy(), suite_sprintf(), NULL};

    for (int i = 0; suite_array[i] != NULL; i++) {
        SRunner *runner = srunner_create(suite_array[i]);
        srunner_set_fork_status(runner, CK_NOFORK);
        srunner_run_all(runner, CK_NORMAL);
        srunner_free(runner);
    }

    return 0;
}