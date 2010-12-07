/**
* @file test_rs232.c
* @brief RS232 Test-Script
*/

#include <test_helper.h>
#include <rs232.h>
#include <rs232_shared_memory.h>

/**
 * @brief Hardware-Initialisierung testen
 * @pre RS232 ist noch nicht initialisiert
 */
START_TEST_FUNC(test_rs232_init_check_for_correct_hardware_configuration)
{
	rs232_init();
	
	/* Nachbedingungen prüfen */
	assert_is_true(BD == 1, "Baudratengenerator wurde nicht eingeschaltet");
	assert_is_true(SM0 == 0 && SM1 == 1, "Falscher Modus für den Baudratengenerator");
	assert_is_true(SRELH == 0x03 && SRELL == 0xDF, "Falsche Gewschwindigkeit");
	assert_is_true(REN == 1 && TI == 1, "Serielle Empfang wurde nicht eingeschaltet");
	assert_is_true(ES == 1, "Serielle Interrupts wurden nicht eingeschaltet");
}
END_TEST_FUNC

/**
 * @brief Senden eines Zeichens
 * @pre RS232 ist bereits initialisiert
 */
START_TEST_FUNC(test_rs232_test_send_character)
{
	
}
END_TEST_FUNC

ctest_suite *test_rs232_create_suite(void)
{
    ctest_suite *suite = ctest_suite_create("rs232");

    ctest_suite_add_test_func(suite, test_rs232_init_check_for_correct_hardware_configuration);

    return suite;
}

