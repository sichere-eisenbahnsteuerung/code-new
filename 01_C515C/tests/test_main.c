
#include "test_helper.h"

extern Suite *ringbuffer_suite_create(void);

int main(int argc, char **argv)
{
#if 0
	struct test_helper *rbtest;

	/* Create all test helpers */
	rbtest = test_helper_create(ringbuffer_suite_create());

	/* Execute all test helpers */
	test_helper_execute_all(rbtest);

	/* FIXME fetch the result from all test helpers */

	/* Free all test helpers */
	test_helper_free(rbtest);
#endif
	return 0;
}
