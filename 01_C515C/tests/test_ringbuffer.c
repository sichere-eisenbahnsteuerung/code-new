
#include "test_helper.h"

#include <ringbuffer.h>

/*
 * @brief This tests the ringbuffer_init method with a NULL value for the first parameter
 */
START_TEST(test_ringbuffer_init_null_parameter)
{
	ringbuffer_init(NULL);
}
END_TEST

/*
 * @brief This tests checks wether the ringbuffer gets successfull intialized
 */
START_TEST(test_ringbuffer_init_correct_run)
{
	ringbuffer_t rb;
	ringbuffer_init(&rb);

	fail_unless(rb.read_position == 0, 
				"Intial read position for the ring buffer is not correct");
	fail_unless(rb.write_position == 0, 
				"Intial write position for the ring buffer is not correct");
	fail_unless(rb.size == 0,
				"Initial size of the ring buffer is not correct - should always be null");
}
END_TEST

Suite *ringbuffer_suite_create(void)
{
	Suite *s = suite_create("ringbuffer");

	TCase *tc_core = tcase_create("core");
	tcase_add_test(tc_core, test_ringbuffer_init_null_parameter);
	tcase_add_test(tc_core, test_ringbuffer_init_correct_run);

	suite_add_tcase(s, tc_core);

	return s;
}
