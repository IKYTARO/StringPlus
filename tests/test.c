#include "test.h"

int main(void) {
	Suite *common_suite = test_common_functions();
	Suite *sprintf_suite = test_sprintf();

	SRunner *runner = srunner_create(common_suite);
	srunner_add_suite(runner, sprintf_suite);
	
    srunner_set_fork_status(runner, CK_NOFORK);
	srunner_run_all(runner, CK_NORMAL);
	
	srunner_free(runner);
	
	return 0;
}