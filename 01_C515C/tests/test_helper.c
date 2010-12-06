
#include "test_helper.h"

struct test_helper 
{
	const char	*name;
	Suite		*suite;
	SRunner		*runner;
};

extern char *current_test_date;

struct test_helper *test_helper_create(Suite *suite, const char *name)
{
	char buffer[200];

	if (suite == NULL || name == NULL)
		return NULL;

	struct test_helper *helper = (struct test_helper*)malloc(sizeof(struct test_helper));

	helper->name = name;
	helper->suite = suite;
	helper->runner = srunner_create(helper->suite);

	snprintf(buffer, 200, "logs/%s/%s.xml", current_test_date, helper->name);
	srunner_set_xml(helper->runner, strdup(buffer));

	return helper;
}

void test_helper_execute_all(struct test_helper *helper)
{
	srunner_run_all(helper->runner, CK_VERBOSE);
}

void test_helper_free(struct test_helper *helper)
{
	if (helper->runner != NULL)
	{
		srunner_free(helper->runner);
	}

	free(helper);
}

