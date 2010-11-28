#ifndef _TEST_HELPER_H_
#define _TEST_HELPER_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "hardware_simulator.h"

struct test_helper;

struct test_helper *test_helper_create(Suite *suite);
void test_helper_execute_all(struct test_helper *helper);
void test_helper_free(struct test_helper *helper);

#endif

