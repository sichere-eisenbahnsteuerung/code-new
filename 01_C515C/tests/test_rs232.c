
#include "test_helper.h"
#include <rs232.h>

extern char wait_for_send;

/*
 * @brief Bla Blup ...
 */
START_TEST(test_rs232_init_check_for_correct_hardware_configuration)
{
	RS232_init();

	/* Nachbedingungen prüfen */
	fail_unless(BD == 1, "Baudratengenerator wurde nicht eingeschaltet");
	fail_unless(SM0 == 0 && SM1 == 1, "Falscher Modus für den Baudratengenerator");
	fail_unless(SRELH == 0x03 && SRELL == 0xDF, "Falsche Gewschwindigkeit");
	fail_unless(REN == 1 && TI == 1, "Serielle Empfang wurde nicht eingeschaltet");
	fail_unless(ES == 1, "Serielle Interrupts wurden nicht eingeschaltet");
	fail_unless(wait_for_send == 0, "Falscher Warte-Modus für die Work-Funktionalität");
}
END_TEST

Suite *test_rs232_create_suite(void)
{
	Suite *s = suite_create("rs232");

	TCase *tc_core = tcase_create("init");
	tcase_add_test(tc_core, test_rs232_init_check_for_correct_hardware_configuration);

	suite_add_tcase(s, tc_core);

	return s;
}

