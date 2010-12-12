/**
 * @file
 * @ingroup unittest
 * @brief XpressNet Test-Script
 *
 * Führt den XpressNet-Unittest durch (Initialisierung, Senden und Empfangen).
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 *
 * @todo Bytes für Befehle überprüfen.
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

// Weiche 1
static uint8_t weiche1_geradeaus1[] = {0x52, 0x00, 0x87};
static uint8_t weiche1_geradeaus2[] = {0x52, 0x00, 0x8E};
static uint8_t weiche1_abbiegen1[]  = {0x52, 0x00, 0x86};
static uint8_t weiche1_abbiegen2[] = {0x52, 0x00, 0x8F};

// Weiche 2
static uint8_t weiche2_geradeaus1[] = {0x52, 0x01, 0x81};
static uint8_t weiche2_geradeaus2[] = {0x52, 0x01, 0x88};
static uint8_t weiche2_abbiegen1[]  = {0x52, 0x01, 0x80};
static uint8_t weiche2_abbiegen2[] = {0x52, 0x01, 0x89};

// Weiche 3
static uint8_t weiche3_geradeaus1[] = {0x52, 0x00, 0x85};
static uint8_t weiche3_geradeaus2[] = {0x52, 0x00, 0x8C};
static uint8_t weiche3_abbiegen1[]  = {0x52, 0x00, 0x84};
static uint8_t weiche3_abbiegen2[] = {0x52, 0x00, 0x8D};

// Entkuppler 1
static uint8_t entkuppler1_deaktivieren[] = {0x52, 0x01, 0x84};
static uint8_t entkuppler1_aktivieren[] = {0x52, 0x01, 0x8C};

// Entkuppler 2
static uint8_t entkuppler2_deaktivieren[] = {0x52, 0x01, 0x82};
static uint8_t entkuppler2_aktivieren[] = {0x52, 0x01, 0x8A};

// Lok 1
static uint8_t lok1_v0[] = {0xE4, 0x13, 0x00, 0x01, 0x00};
static uint8_t lok1_v1[] = {0xE4, 0x13, 0x00, 0x01, 0x08};
static uint8_t lok1_v2[] = {0xE4, 0x13, 0x00, 0x01, 0x1F};
static uint8_t lok1_v3[] = {0xE4, 0x13, 0x00, 0x01, 0xDD};

// Lok 2
static uint8_t lok2_v0[] = {0xE4, 0x13, 0x00, 0x02, 0x00};
static uint8_t lok2_v1[] = {0xE4, 0x13, 0x00, 0x02, 0x08};
static uint8_t lok2_v2[] = {0xE4, 0x13, 0x00, 0x02, 0x1F};
static uint8_t lok2_v3[] = {0xE4, 0x13, 0x00, 0x02, 0xDD};

	
/**
 * @brief XpressNet initialisieren
 */
START_TEST_FUNC(test_init_xpressnet)  
{
	rs232_output_read_pos = rs232_output_write_pos = 0;
	rs232_input_read_pos = rs232_input_write_pos = 0;
	
	xpressnet_init();
	
	assert_is_true(streckenbefehl_ev_xpressnet.target == IDLE, "Nach Initialisierung Streckenbefehl nicht IDLE!");
}

/**
 * @brief Weichenbefehle für Weiche 1 testen
 * @pre Kein Streckenbefehl gesetzt.
 */
START_TEST_FUNC(test_xpressnet_weiche1)
{
	// Weiche 1
	streckenbefehl_ev_xpressnet.target = WEICHE1;
	streckenbefehl_ev_xpressnet.command = 0; // Geradeaus
	xpressnet_work();
	assert_is_true(testCommand("Weiche 1 geradeaus 1", weiche1_geradeaus1, 4, WEICHE1)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(testCommand("Weiche 1 geradeaus 2", weiche1_geradeaus2, 4, IDLE)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
	
	streckenbefehl_ev_xpressnet.target = WEICHE1;
	streckenbefehl_ev_xpressnet.command = 1; // Abbiegen
	xpressnet_work();
	assert_is_true(testCommand("Weiche 1 abbiegen 1", weiche1_abbiegen1, 4, WEICHE1)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(testCommand("Weiche 1 abbiegen 2", weiche1_abbiegen2, 4, IDLE)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
	
	
}
END_TEST_FUNC


/**
 * @brief Weichenbefehle für Weiche 2 testen
 * @pre Kein Streckenbefehl gesetzt.
 */
START_TEST_FUNC(test_xpressnet_weiche2)
{
	// Weiche 2
	streckenbefehl_ev_xpressnet.target = WEICHE2;
	streckenbefehl_ev_xpressnet.command = 0; // Geradeaus
	xpressnet_work();
	assert_is_true(testCommand("Weiche 2 geradeaus 1", weiche2_geradeaus1, 4, WEICHE2)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(testCommand("Weiche 2 geradeaus 2", weiche2_geradeaus2, 4, IDLE)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
	
	streckenbefehl_ev_xpressnet.target = WEICHE2;
	streckenbefehl_ev_xpressnet.command = 1; // Abbiegen
	xpressnet_work();
	assert_is_true(testCommand("Weiche 2 abbiegen 1", weiche2_abbiegen1, 4, WEICHE2)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(testCommand("Weiche 2 abbiegen 2", weiche2_abbiegen2, 4, IDLE)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
	
	
}
END_TEST_FUNC

/**
 * @brief Weichenbefehle für Weiche 3 testen
 * @pre Kein Streckenbefehl gesetzt.
 */
START_TEST_FUNC(test_xpressnet_weiche3)
{
	// Weiche 3
	streckenbefehl_ev_xpressnet.target = WEICHE3;
	streckenbefehl_ev_xpressnet.command = 0; // Geradeaus
	xpressnet_work();
	assert_is_true(testCommand("Weiche 3 geradeaus 1", weiche3_geradeaus1, 4, WEICHE3)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(testCommand("Weiche 3 geradeaus 2", weiche3_geradeaus2, 4, IDLE)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
	
	streckenbefehl_ev_xpressnet.target = WEICHE3;
	streckenbefehl_ev_xpressnet.command = 1; // Abbiegen
	xpressnet_work();
	assert_is_true(testCommand("Weiche 3 abbiegen 1", weiche3_abbiegen1, 4, WEICHE3)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(testCommand("Weiche 3 abbiegen 2", weiche3_abbiegen2, 4, IDLE)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
	
	
}
END_TEST_FUNC


/**
 * @brief Entkupplerbefehle für Entkuppler 1 testen
 * @pre Kein Streckenbefehl gesetzt.
 */
START_TEST_FUNC(test_xpressnet_entkuppler1)
{
	// Entkuppler 1
	streckenbefehl_ev_xpressnet.target = ENTKUPPLER1;
	streckenbefehl_ev_xpressnet.command = 0; // Geradeaus
	xpressnet_work();
	assert_is_true(testCommand("Entkuppler 1deaktivieren", entkuppler1_deaktivieren, 4, ENTKUPPLER1)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(testCommand("Entkuppler 1 aktiveren", entkuppler1_aktivieren, 4, IDLE)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
}
END_TEST_FUNC

/**
 * @brief Entkupplerbefehle für Entkuppler 2 testen
 * @pre Kein Streckenbefehl gesetzt.
 */
START_TEST_FUNC(test_xpressnet_entkuppler2)
{
	// Entkuppler 1
	streckenbefehl_ev_xpressnet.target = ENTKUPPLER2;
	streckenbefehl_ev_xpressnet.command = 0; // Geradeaus
	xpressnet_work();
	assert_is_true(testCommand("Entkuppler 1deaktivieren", entkuppler2_deaktivieren, 4, ENTKUPPLER2)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(testCommand("Entkuppler 1 aktiveren", entkuppler2_aktivieren, 4, IDLE)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
}
END_TEST_FUNC

/**
 * @brief Lokbefehle für Lok1 testen
 * @pre XpressNet initialisiert
 */
START_TEST_FUNC(test_xpressnet_lok1)
{
	streckenbefehl_ev_xpressnet.target = LOK1;
	streckenbefehl_ev_xpressnet.command = 0;
	xpressnet_work();
	assert_is_true(testCommand("Lok 1 Stop", lok1_v0, 6, IDLE)==0, "Fehler in Befehlssequenz!");
	
	streckenbefehl_ev_xpressnet.target = LOK1;
	streckenbefehl_ev_xpressnet.command = 1;
	xpressnet_work();
	assert_is_true(testCommand("Lok 1 Abkoppeln", lok1_v1, 6, IDLE)==0, "Fehler in Befehlssequenz!");
	
	streckenbefehl_ev_xpressnet.target = LOK1;
	streckenbefehl_ev_xpressnet.command = 2;
	xpressnet_work();
	assert_is_true(testCommand("Lok 1 Ankoppeln", lok1_v2, 6, IDLE)==0, "Fehler in Befehlssequenz!");
	
	streckenbefehl_ev_xpressnet.target = LOK1;
	streckenbefehl_ev_xpressnet.command = 3;
	xpressnet_work();
	assert_is_true(testCommand("Lok 1 Fahrt", lok1_v3, 6, IDLE)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
	
}
END_TEST_FUNC


/**
 * @brief Lokbefehle für Lok1 testen
 * @pre XpressNet initialisiert
 */
START_TEST_FUNC(test_xpressnet_lok2)
{
	streckenbefehl_ev_xpressnet.target = LOK2;
	streckenbefehl_ev_xpressnet.command = 0;
	xpressnet_work();
	assert_is_true(testCommand("Lok 2 Stop", lok2_v0, 6, IDLE)==0, "Fehler in Befehlssequenz!");
	
	streckenbefehl_ev_xpressnet.target = LOK2;
	streckenbefehl_ev_xpressnet.command = 1;
	xpressnet_work();
	assert_is_true(testCommand("Lok 2 Abkoppeln", lok2_v1, 6, IDLE)==0, "Fehler in Befehlssequenz!");
	
	streckenbefehl_ev_xpressnet.target = LOK2;
	streckenbefehl_ev_xpressnet.command = 2;
	xpressnet_work();
	assert_is_true(testCommand("Lok 2 Ankoppeln", lok2_v2, 6, IDLE)==0, "Fehler in Befehlssequenz!");
	
	streckenbefehl_ev_xpressnet.target = LOK2;
	streckenbefehl_ev_xpressnet.command = 3;
	xpressnet_work();
	assert_is_true(testCommand("Lok 2 Fahrt", lok2_v3, 6, IDLE)==0, "Fehler in Befehlssequenz!");
	xpressnet_work();
	assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
	
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
	
    ctest_suite_add_test_func(suite, test_init_xpressnet);
    ctest_suite_add_test_func(suite, test_xpressnet_weiche1);
    ctest_suite_add_test_func(suite, test_xpressnet_weiche2);
    ctest_suite_add_test_func(suite, test_xpressnet_weiche3);
    ctest_suite_add_test_func(suite, test_xpressnet_entkuppler1);
    ctest_suite_add_test_func(suite, test_xpressnet_entkuppler2);
    ctest_suite_add_test_func(suite, test_xpressnet_lok1);
    ctest_suite_add_test_func(suite, test_xpressnet_lok2);

    return suite;
}


/** @brief Testet die Bytes eines Befehls */
int testCommand(char *description, uint8_t *command, int command_length, streckenbefehl_ziel result_target) {
	char problem[200];
	uint8_t i = 0, input, xor = 0;
	
	sprintf(problem, "Falsche Befehlslänge (%i statt %i) - %s", bytes_to_read(), command_length, description);
	assert_is_true(bytes_to_read() == command_length, problem);
	
	for(i=0;i<command_length-1;i++) {
		input = read_byte();
		sprintf(problem, "Fehler Byte %i (0x%X statt 0x%X) - %s", i, input, command[i], description);
		xor ^= command[i];
		assert_is_true(input == command[i], problem);
	}
	input = read_byte();
	sprintf(problem, "Fehler XOR-Byte (0x%X statt 0x%X) - %s", input, xor, description);
	assert_is_true(input == xor, problem);
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
	  
