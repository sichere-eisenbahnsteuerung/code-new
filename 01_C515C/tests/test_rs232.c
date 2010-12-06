
#include <test_helper.h>
#include <rs232.h>

extern char wait_for_send;

/*
 * @brief Bla Blup ...
 */
START_TEST_FUNC(test_rs232_init_check_for_correct_hardware_configuration)
{
	RS232_init();

	printf("test_rs232_init_check_for_correct_hardware_configuration\n");

	/* Nachbedingungen prüfen */
	assert_is_true(BD == 0, "Baudratengenerator wurde nicht eingeschaltet");
	assert_is_true(SM0 == 0 && SM1 == 1, "Falscher Modus für den Baudratengenerator");
	assert_is_true(SRELH == 0x03 && SRELL == 0xDF, "Falsche Gewschwindigkeit");
	assert_is_true(REN == 1 && TI == 1, "Serielle Empfang wurde nicht eingeschaltet");
	assert_is_true(ES == 1, "Serielle Interrupts wurden nicht eingeschaltet");
	assert_is_true(wait_for_send == 0, "Falscher Warte-Modus für die Work-Funktionalität");
}
END_TEST_FUNC

ctest_suite *test_rs232_create_suite(void)
{
    ctest_suite *suite = ctest_suite_create("rs232");

    ctest_suite_add_test_func(suite, test_rs232_init_check_for_correct_hardware_configuration);

    return suite;
}

