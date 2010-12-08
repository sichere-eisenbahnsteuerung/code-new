
/**
* @file test_rs232.c
* @brief RS232 Test-Script
*/

#include <test_helper.h>
#include <rs232.h>
#include <rs232_shared_memory.h>

extern char wait_for_send;

/*
 * @brief Bla Blup ...
/**
 * @brief Hardware-Initialisierung testen
 * @pre RS232 ist noch nicht initialisiert
 */
START_TEST_FUNC(test_rs232_init_check_for_correct_hardware_configuration)
{
	RS232_init();

	printf("test_rs232_init_check_for_correct_hardware_configuration\n");

	rs232_init();
	
	/* Nachbedingungen prüfen */
	assert_is_true(BD == 0, "Baudratengenerator wurde nicht eingeschaltet");
	assert_is_true(BD == 1, "Baudratengenerator wurde nicht eingeschaltet");
	assert_is_true(SM0 == 0 && SM1 == 1, "Falscher Modus für den Baudratengenerator");
	assert_is_true(SRELH == 0x03 && SRELL == 0xDF, "Falsche Gewschwindigkeit");
	assert_is_true(REN == 1 && TI == 1, "Serielle Empfang wurde nicht eingeschaltet");
	assert_is_true(ES == 1, "Serielle Interrupts wurden nicht eingeschaltet");
	assert_is_true(wait_for_send == 0, "Falscher Warte-Modus für die Work-Funktionalität");
}
END_TEST_FUNC

/**
 * @brief Senden eines Zeichens
 * @pre RS232 ist bereits initialisiert
 */
START_TEST_FUNC(test_rs232_test_send_character)
{
	ctest_register_wait_for_handler(&simulate_send_char);
	
	ctest_register_wait_for_handler(NULL);
}
END_TEST_FUNC

int simulate_send_char() {
	SBUF = 0;
	TI = 1;
	rs232_interrupt();
	assert_is_true(TI == 0, "TI-Flag nicht zurückgesetzt");
}

int simulate_read_char(uint8_t c) {
	SBUF = c;
	RI = 1;
	rs232_interrupt();
	assert_is_true(RI == 0, "TI-Flag nicht zurückgesetzt");
}

ctest_suite *test_rs232_create_suite(void)
{
    ctest_suite *suite = ctest_suite_create("rs232");

    ctest_suite_add_test_func(suite, test_rs232_init_check_for_correct_hardware_configuration);

    return suite;
}

