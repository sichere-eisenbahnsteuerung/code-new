
#include "test_helper.h"

struct test_helper 
{
	Suite		*suite;
	SRunner		*runner;
};

struct test_helper *test_helper_create(Suite *suite)
{
	struct test_helper *helper = (struct test_helper*)malloc(sizeof(struct test_helper));

	helper->suite = suite;
	helper->runner = srunner_create(helper->suite);

	return helper;
}

void test_helper_execute_all(struct test_helper *helper)
{
	srunner_run_all(helper->runner, CK_NORMAL);
}

void test_helper_free(struct test_helper *helper)
{
	if (helper->runner != NULL)
	{
		srunner_free(helper->runner);
	}

	free(helper);
}

