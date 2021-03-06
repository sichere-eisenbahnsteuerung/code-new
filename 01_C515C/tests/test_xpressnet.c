/*
 *    XpressNet Test-Script
 *    Copyright (C) 2011 Hanno Fellmann
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
 * @brief XpressNet Test-Script
 *
 * F�hrt den XpressNet-Unittest durch (Initialisierung, Senden und Empfangen).
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 */

#include <test_helper.h>
#include <xpressnet.h>
#include <rs232_shared_memory.h>

static int testCommand(char *description, uint8_t *command, int command_length, streckenbefehl_ziel result_target, bool sendSchalt, bool sendAnswer);
static uint8_t write_byte(uint8_t b);
static uint8_t max_bytes_to_write();
static uint8_t bytes_to_read();
static uint8_t read_byte();
static uint8_t peek_byte();

// Weiche 1
static uint8_t weiche1_geradeaus1[] = {0x52, 0x00, 0x86};
static uint8_t weiche1_geradeaus2[] = {0x52, 0x00, 0x8F};
static uint8_t weiche1_abbiegen1[]  = {0x52, 0x00, 0x87};
static uint8_t weiche1_abbiegen2[]  = {0x52, 0x00, 0x8E};

// Weiche 2
static uint8_t weiche2_geradeaus1[] = {0x52, 0x01, 0x80};
static uint8_t weiche2_geradeaus2[] = {0x52, 0x01, 0x89};
static uint8_t weiche2_abbiegen1[]  = {0x52, 0x01, 0x81};
static uint8_t weiche2_abbiegen2[]  = {0x52, 0x01, 0x88};

// Weiche 3
static uint8_t weiche3_geradeaus1[] = {0x52, 0x00, 0x84};
static uint8_t weiche3_geradeaus2[] = {0x52, 0x00, 0x8D};
static uint8_t weiche3_abbiegen1[]  = {0x52, 0x00, 0x85};
static uint8_t weiche3_abbiegen2[]  = {0x52, 0x00, 0x8C};

// Entkuppler 1
static uint8_t entkuppler1_deaktivieren[] = {0x52, 0x01, 0x84};
static uint8_t entkuppler1_aktivieren[] =   {0x52, 0x01, 0x8C};

// Entkuppler 2
static uint8_t entkuppler2_deaktivieren[] = {0x52, 0x01, 0x82};
static uint8_t entkuppler2_aktivieren[] =   {0x52, 0x01, 0x8A};

// Lok 1
static uint8_t lok1_v0[] = {0xE4, 0x13, 0x00, 0x01, 0x00};
static uint8_t lok1_v1[] = {0xE4, 0x13, 0x00, 0x01, 0x88};
static uint8_t lok1_v2[] = {0xE4, 0x13, 0x00, 0x01, 0x1F};
static uint8_t lok1_v3[] = {0xE4, 0x13, 0x00, 0x01, 0xDD};

// Lok 2
static uint8_t lok2_v0[] = {0xE4, 0x13, 0x00, 0x02, 0x00};
static uint8_t lok2_v1[] = {0xE4, 0x13, 0x00, 0x02, 0x88};
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

    assert_is_true(streckenbefehl_xpressnet.target == IDLE, "Nach Initialisierung Streckenbefehl nicht IDLE!");
}

/**
 * @brief Weichenbefehle f�r Weiche 1 testen
 * @pre Kein Streckenbefehl gesetzt.
 */
START_TEST_FUNC(test_xpressnet_weiche1)
{
    // Weiche 1
    streckenbefehl_xpressnet.target = WEICHE_A;
    streckenbefehl_xpressnet.command = 0; // Geradeaus
    xpressnet_work();
    assert_is_true(testCommand("Weiche 1 geradeaus 1", weiche1_geradeaus1, 4, WEICHE_A, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(testCommand("Weiche 1 geradeaus 2", weiche1_geradeaus2, 4, IDLE, TRUE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");

    streckenbefehl_xpressnet.target = WEICHE_A;
    streckenbefehl_xpressnet.command = 1; // Abbiegen
    xpressnet_work();
    assert_is_true(testCommand("Weiche 1 abbiegen 1", weiche1_abbiegen1, 4, WEICHE_A, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(testCommand("Weiche 1 abbiegen 2", weiche1_abbiegen2, 4, IDLE, TRUE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");


}
END_TEST_FUNC


/**
 * @brief Weichenbefehle f�r Weiche 2 testen
 * @pre Kein Streckenbefehl gesetzt.
 */
START_TEST_FUNC(test_xpressnet_weiche2)
{
    // Weiche 2
    streckenbefehl_xpressnet.target = WEICHE_B;
    streckenbefehl_xpressnet.command = 0; // Geradeaus
    xpressnet_work();
    assert_is_true(testCommand("Weiche 2 geradeaus 1", weiche2_geradeaus1, 4, WEICHE_B, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(testCommand("Weiche 2 geradeaus 2", weiche2_geradeaus2, 4, IDLE, TRUE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");

    streckenbefehl_xpressnet.target = WEICHE_B;
    streckenbefehl_xpressnet.command = 1; // Abbiegen
    xpressnet_work();
    assert_is_true(testCommand("Weiche 2 abbiegen 1", weiche2_abbiegen1, 4, WEICHE_B, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(testCommand("Weiche 2 abbiegen 2", weiche2_abbiegen2, 4, IDLE, TRUE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");


}
END_TEST_FUNC

/**
 * @brief Weichenbefehle f�r Weiche 3 testen
 * @pre Kein Streckenbefehl gesetzt.
 */
START_TEST_FUNC(test_xpressnet_weiche3)
{
    // Weiche 3
    streckenbefehl_xpressnet.target = WEICHE_C;
    streckenbefehl_xpressnet.command = 0; // Geradeaus
    xpressnet_work();
    assert_is_true(testCommand("Weiche 3 geradeaus 1", weiche3_geradeaus1, 4, WEICHE_C, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(testCommand("Weiche 3 geradeaus 2", weiche3_geradeaus2, 4, IDLE, TRUE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");

    streckenbefehl_xpressnet.target = WEICHE_C;
    streckenbefehl_xpressnet.command = 1; // Abbiegen
    xpressnet_work();
    assert_is_true(testCommand("Weiche 3 abbiegen 1", weiche3_abbiegen1, 4, WEICHE_C, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(testCommand("Weiche 3 abbiegen 2", weiche3_abbiegen2, 4, IDLE, TRUE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");


}
END_TEST_FUNC


/**
 * @brief Entkupplerbefehle f�r Entkuppler 1 testen
 * @pre Kein Streckenbefehl gesetzt.
 */
START_TEST_FUNC(test_xpressnet_entkuppler1)
{
    // Entkuppler 1
    streckenbefehl_xpressnet.target = ENTKUPPLER_E1;
    streckenbefehl_xpressnet.command = 0; // Geradeaus
    xpressnet_work();
    assert_is_true(testCommand("Entkuppler 1deaktivieren", entkuppler1_deaktivieren, 4, ENTKUPPLER_E1, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(testCommand("Entkuppler 1 aktiveren", entkuppler1_aktivieren, 4, IDLE, TRUE, FALSE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
}
END_TEST_FUNC

/**
 * @brief Entkupplerbefehle f�r Entkuppler 2 testen
 * @pre Kein Streckenbefehl gesetzt.
 */
START_TEST_FUNC(test_xpressnet_entkuppler2)
{
    // Entkuppler 1
    streckenbefehl_xpressnet.target = ENTKUPPLER_E2;
    streckenbefehl_xpressnet.command = 0; // Geradeaus
    xpressnet_work();
    assert_is_true(testCommand("Entkuppler 1deaktivieren", entkuppler2_deaktivieren, 4, ENTKUPPLER_E2, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(testCommand("Entkuppler 1 aktiveren", entkuppler2_aktivieren, 4, IDLE, TRUE, FALSE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
}
END_TEST_FUNC

/**
 * @brief Lokbefehle f�r Lok1 testen
 * @pre XpressNet initialisiert
 */
START_TEST_FUNC(test_xpressnet_lok1)
{
    streckenbefehl_xpressnet.target = LOK_RED;
    streckenbefehl_xpressnet.command = 0;
    xpressnet_work();
    assert_is_true(testCommand("Lok 1 Stop", lok1_v0, 6, IDLE, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");

    streckenbefehl_xpressnet.target = LOK_RED;
    streckenbefehl_xpressnet.command = 1;
    xpressnet_work();
    assert_is_true(testCommand("Lok 1 Abkoppeln", lok1_v1, 6, IDLE, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");

    streckenbefehl_xpressnet.target = LOK_RED;
    streckenbefehl_xpressnet.command = 2;
    xpressnet_work();
    assert_is_true(testCommand("Lok 1 Ankoppeln", lok1_v2, 6, IDLE, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");
    
    streckenbefehl_xpressnet.target = LOK_RED;
    streckenbefehl_xpressnet.command = 3;
    xpressnet_work();
    assert_is_true(testCommand("Lok 1 Fahrt", lok1_v3, 6, IDLE, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");
    
}
END_TEST_FUNC


/**
 * @brief Lokbefehle f�r Lok1 testen
 * @pre XpressNet initialisiert
 */
START_TEST_FUNC(test_xpressnet_lok2)
{
    streckenbefehl_xpressnet.target = LOK_BLACK;
    streckenbefehl_xpressnet.command = 0;
    xpressnet_work();
    assert_is_true(testCommand("Lok 2 Stop", lok2_v0, 6, IDLE, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");

    streckenbefehl_xpressnet.target = LOK_BLACK;
    streckenbefehl_xpressnet.command = 1;
    xpressnet_work();
    assert_is_true(testCommand("Lok 2 Abkoppeln", lok2_v1, 6, IDLE, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");

    streckenbefehl_xpressnet.target = LOK_BLACK;
    streckenbefehl_xpressnet.command = 2;
    xpressnet_work();
    assert_is_true(testCommand("Lok 2 Ankoppeln", lok2_v2, 6, IDLE, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");

    streckenbefehl_xpressnet.target = LOK_BLACK;
    streckenbefehl_xpressnet.command = 3;
    xpressnet_work();
    assert_is_true(testCommand("Lok 2 Fahrt", lok2_v3, 6, IDLE, FALSE, TRUE)==0, "Fehler in Befehlssequenz!");
    xpressnet_work();
    assert_is_true(bytes_to_read() == 0, "Daten gesendet ohne gesetzten Befehl!");

}
END_TEST_FUNC

/**
 * @brief Erstellt die Test Suite
 *
 * Erstellt eine Test Suite, die die Initialisierung, das Senden und das Empfangen �ber RS232 testet.
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
static int testCommand(char *description, uint8_t *command, int command_length, streckenbefehl_ziel result_target, bool sendSchalt, bool sendAnswer) {
    char problem[200];
    uint8_t i = 0, input, xor = 0;

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
    assert_is_true(bytes_to_read() == 0, "Befehl gesendet ohne Best�tigung!");
    if(sendAnswer) {
        write_byte(0x01);
        write_byte(0x04);
        xpressnet_work();
        assert_is_true(bytes_to_read() == 0, "Befehl gesendet bei zu unvollst�ndiger Best�tigung!");
        write_byte(0x02);
        xpressnet_work();
        assert_is_true(bytes_to_read() == 0, "Befehl gesendet bei zu falscher Best�tigung!");
        write_byte(0x01);
        write_byte(0x04);
        write_byte(0x05);
    }
    if(sendSchalt) {
        write_byte(0x42);
        write_byte(0x00);
        write_byte(0x01);
        xpressnet_work();
        assert_is_true(bytes_to_read() == 0, "Befehl gesendet bei zu unvollst�ndiger Best�tigung!");
        write_byte(0x41);
        xpressnet_work();
        write_byte(0x42);
        write_byte(0x00);
        write_byte(0x01);
        write_byte(0x43);
    }
       
    xpressnet_work();
    sprintf(problem, "Streckenbefehl ist nicht korrekt - %s", description);
    assert_is_true(streckenbefehl_xpressnet.target == result_target, problem);
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

