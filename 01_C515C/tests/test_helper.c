/*
 *    test helper
 *    Copyright (C) 2011 Hochschule Bremen
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

