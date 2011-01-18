/*
 *    test rs232
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

/**
 * @file
 * @ingroup unittest
 * @brief RS232 Test-Script
 *
 * Führt den RS232-Unittest durch (Initialisierung, Senden und Empfangen).
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 */

#include <test_helper.h>
#include <rs232.h>

int simulate_send_byte();
int simulate_read_byte(uint8_t c);
static uint8_t write_byte(uint8_t b);
static uint8_t max_bytes_to_write();
static uint8_t bytes_to_read();
static uint8_t read_byte();
static uint8_t peek_byte();

// Zwischenspeicher für gesendete Bytes zur Kontrolle
static uint8_t bytes_sent[20] = {0}, bytes_sent_idx = 0;

/**
 * @brief Hardware-Initialisierung testen
 * @pre Keine.
 */
START_TEST_FUNC(test_rs232_init_check_for_correct_hardware_configuration)
{

	rs232_init();
	
	/* Nachbedingungen prüfen */
	assert_is_true(BD == 1, "Baudratengenerator wurde nicht eingeschaltet");
	assert_is_true(SM0 == 0 && SM1 == 1, "Falscher Modus für den Baudratengenerator");
	assert_is_true(SRELH == 0x03 && SRELL == 0xE0, "Falsche Gewschwindigkeit");
	assert_is_true(REN == 1 && TI == 1, "Serielle Empfang wurde nicht eingeschaltet");
	assert_is_true(ES == 1, "Serielle Interrupts wurden nicht eingeschaltet");
}
END_TEST_FUNC

/**
 * @brief Senden von Zeichen testen
 * @pre RS232 initialisiert.
 *
 * Sendet insgesamt 100 x 4 Zeichen über die RS232-Schnittstelle.
 */
START_TEST_FUNC(test_rs232_test_send_character)
{
	int i=0;
	
	rs232_output_read_pos = rs232_output_write_pos = 0;
	
	ctest_register_wait_for_handler(&simulate_send_byte);
	
	CTS_PIN = 0;
	write_byte(1);
	bytes_sent_idx = 0;
	rs232_work();
	assert_is_true(bytes_sent_idx == 0, "Bytes gesendet, obwohl CTS nicht gesetzt");
	rs232_output_read_pos = rs232_output_write_pos = 0;
	
	CTS_PIN = 1;
	for(i=0;i<100;i++) {
		write_byte(2);
		write_byte(4);
		write_byte(6);
		write_byte(8);
		bytes_sent_idx = 0;
		rs232_work();
		assert_is_true(simulate_send_byte() == 0, "Fehler im simulierten Senden!");
		assert_is_true(bytes_sent_idx == 4, "Falsche Anzahl gesendeter Bytes");
		assert_is_true(bytes_sent[0] == 2, "Byte 1 fehlerhaft gesendet");
		assert_is_true(bytes_sent[1] == 4, "Byte 2 fehlerhaft gesendet");
		assert_is_true(bytes_sent[2] == 6, "Byte 3 fehlerhaft gesendet");
		assert_is_true(bytes_sent[3] == 8, "Byte 4 fehlerhaft gesendet");
	}
}
END_TEST_FUNC



/**
 * @brief Empfangen von Zeichen testen
 * @pre RS232 initialisiert.
 *
 * Empfängt insgesamt 100 x 4 Zeichen über die RS232-Schnittstelle.
 */
START_TEST_FUNC(test_rs232_test_receive_character)
{
	int i=0;
	
	ctest_register_wait_for_handler(&simulate_send_byte);
    
	rs232_input_read_pos = rs232_input_write_pos = 0;
	
	for(i=0;i<100;i++) {
		assert_is_true(simulate_read_byte(1) == 0, "Fehler beim simulierten Empfangen!");
		assert_is_true(simulate_read_byte(3) == 0, "Fehler beim simulierten Empfangen!");
		assert_is_true(simulate_read_byte(5) == 0, "Fehler beim simulierten Empfangen!");
		assert_is_true(simulate_read_byte(7) == 0, "Fehler beim simulierten Empfangen!");
		
		rs232_work();
		
		assert_is_true(bytes_to_read() == 4, "Falsche Anzahl empfangener Bytes");
		assert_is_true(read_byte() == 1, "Byte 1 fehlerhaft empfangen");
		assert_is_true(read_byte() == 3, "Byte 2 fehlerhaft empfangen");
		assert_is_true(read_byte() == 5, "Byte 3 fehlerhaft empfangen");
		assert_is_true(read_byte() == 7, "Byte 4 fehlerhaft empfangen");
	}
}
END_TEST_FUNC

/**
 * @brief Simuliert die Sende-Hardwarefunktion
 * @warning Null kann nicht gesendet werden! Die Simulation ist nicht möglich, weil Änderungen an SBUF nicht feststelltbar sind. Deshalb wird Null als "nichts zu senden" interpretiert.
 */
int simulate_send_byte() {
	if(SBUF != 0) {							
		bytes_sent[bytes_sent_idx] = SBUF;
		bytes_sent_idx++;
		
		SBUF = 0;
		TI = 1;
		rs232_interrupt();
		assert_is_true(TI == 0, "TI-Flag nicht zurückgesetzt");
	}
}

/**
 * @brief Simuliert die Sende-Hardwarefunktion
 */
int simulate_read_byte(uint8_t c) {
	SBUF = c;
	RI = 1;
	rs232_interrupt();
	SBUF = 0;
	assert_is_true(RI == 0, "TI-Flag nicht zurückgesetzt");
}

/**
 * @brief Erstellt die Test Suite
 *
 * Erstellt eine Test Suite, die die Initialisierung, das Senden und das Empfangen über RS232 testet.
 */
ctest_suite *test_rs232_create_suite(void)
{
    ctest_suite *suite = ctest_suite_create("RS232");

    ctest_suite_add_test_func(suite, test_rs232_init_check_for_correct_hardware_configuration);
    ctest_suite_add_test_func(suite, test_rs232_test_send_character);
    ctest_suite_add_test_func(suite, test_rs232_test_receive_character);

    return suite;
}


/*
 * Funktionen zum Lesen und Schreiben der RS232-Ringbuffer
 */

static uint8_t write_byte(uint8_t b) {
	rs232_output_buffer[rs232_output_write_pos] = b;
    rs232_output_write_pos = (rs232_output_write_pos + 1) % RS232_BUFFERSIZE;
	return b;
}

static uint8_t max_bytes_to_write() {
	return (rs232_output_read_pos + RS232_BUFFERSIZE - rs232_output_write_pos - 1) % RS232_BUFFERSIZE;
}

static uint8_t bytes_to_read() {
	return (rs232_input_write_pos + RS232_BUFFERSIZE - rs232_input_read_pos) % RS232_BUFFERSIZE;
}	

static uint8_t read_byte() {
	uint8_t inp;
    inp = rs232_input_buffer[rs232_input_read_pos];	 
    rs232_input_read_pos = (rs232_input_read_pos + 1) % RS232_BUFFERSIZE;
	return inp;
}		

static uint8_t peek_byte() {
	return rs232_input_buffer[rs232_input_read_pos];
}	
	  
