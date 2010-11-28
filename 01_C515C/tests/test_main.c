
#include "test_helper.h"

extern Suite *test_rs232_create_suite(void);

int main(int argc, char **argv)
{
	struct test_helper *rs232test;

	/* Create all test helpers */
	rs232test = test_helper_create(test_rs232_create_suite());

	/* Execute all test helpers */
	test_helper_execute_all(rs232test);

	/* FIXME fetch the result from all test helpers */

	/* Free all test helpers */
	test_helper_free(rs232test);

	return 0;
}

