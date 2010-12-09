/**
 * @file
 * @ingroup unittest
 * @brief XpressNet Test-Script
 *
 * Führt den XpressNet-Unittest durch (Initialisierung, Senden und Empfangen).
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 */

#include <test_helper.h>
#include <xpressnet.h>
#include <rs232_shared_memory.h>

int testCommand(char *description, uint8_t *command, int command_length, streckenbefehl_ziel result_target);
static uint8_t write_byte(uint8_t b);
static uint8_t max_bytes_to_write();
static uint8_t bytes_to_read();
static uint8_t read_byte();
static uint8_t peek_byte();

static uint8_t weiche1_geradeaus1[] = {0x52, 0x00, 0x87, 0xD5};
static uint8_t weiche1_geradeaus2[] = {0x52, 0x00, 0x8E, 0xDC};
static uint8_t weiche1_abbiegen1[]  = {0x52, 0x00, 0x85, 0xD7};
static uint8_t weiche1_abbiegen2[] = {0x52, 0x00, 0x8C, 0xDE};


/**
 * @brief Hardware-Initialisierung testen
 * @pre Kein Streckenbefehl gesetzt.
 */
START_TEST_FUNC(test_xpressnet_weichenbefehle)
{
	int i = 0;
	xpressnet_init();
	
	rs232_output_read_pos = rs232_output_write_pos = 0;
	rs232_input_read_pos = rs232_input_write_pos = 0;
	
	assert_is_true(bytes_to_read() == 0, "RS232-Puffer ist nicht leer!");
	

	streckenbefehl_ev_xpressnet.target = WEICHE1;
	streckenbefehl_ev_xpressnet.command = 0; // Geradeaus
	xpressnet_work();
	testCommand("Weiche 1 geradeaus 1", weiche1_geradeaus1, 4, WEICHE1);
	xpressnet_work();
	testCommand("Weiche 1 geradeaus 2", weiche1_geradeaus2, 4, IDLE);
}
END_TEST_FUNC


/**
 * @brief Erstellt die Test Suite
 *
 * Erstellt eine Test Suite, die die Initialisierung, das Senden und das Empfangen über RS232 testet.
 */
ctest_suite *test_xpressnet_create_suite(void)
{
    ctest_suite *suite = ctest_suite_create("XpressNet");

    ctest_suite_add_test_func(suite, test_xpressnet_weichenbefehle);

    return suite;
}


/** @brief Testet die Bytes eines Befehls */
int testCommand(char *description, uint8_t *command, int command_length, streckenbefehl_ziel result_target) {
	char problem[200];
	uint8_t i = 0, input;
	assert_is_true(bytes_to_read() == command_length, "Falsche Befehlslänge Weichenbefehl!");
	for(i=0;i<command_length;i++) {
		input = read_byte();
		sprintf(problem, "Fehler Byte %i (0x%X statt 0x%X) - %s", i, input, command[i], description);
		assert_is_true(input == command[i], problem);
	}
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Befehl gesendet ohne Bestätigung!");
	write_byte(0x01);
	write_byte(0x04);
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Befehl gesendet bei zu unvollständiger Bestätigung!");
	write_byte(0x02);
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Befehl gesendet bei zu falscher Bestätigung!");
	write_byte(0x01);
	write_byte(0x04);
	write_byte(0x05);
	xpressnet_work();
	sprintf(problem, "Streckenbefehl ist nicht korrekt - %s", description);
	assert_is_true(streckenbefehl_ev_xpressnet.target == result_target, problem);
}
	


/*
 * Funktionen zum Lesen und Schreiben der RS232-Ringbuffer
 */

static uint8_t write_byte(uint8_t b) {
	rs232_input_buffer[rs232_input_write_pos] = b;
    rs232_input_write_pos = (rs232_input_write_pos + 1) % RS232_BUFFERSIZE;
	return b;
}

static uint8_t bytes_to_read() {
	return (rs232_output_write_pos + RS232_BUFFERSIZE - rs232_output_read_pos) % RS232_BUFFERSIZE;
}	

static uint8_t read_byte() {
	uint8_t inp;
    inp = rs232_output_buffer[rs232_output_read_pos];	 
    rs232_output_read_pos = (rs232_output_read_pos + 1) % RS232_BUFFERSIZE;
	return inp;
}		

static uint8_t peek_byte() {
	return rs232_output_buffer[rs232_output_read_pos];
}	
	  