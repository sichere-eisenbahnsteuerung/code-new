/*
 *    Xpressnet-Treiber
 *    Copyright (C) 2011  Hochschule Bremen
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
 * @ingroup xpressnet_rs232
 * @brief Xpressnet-Treiber
 * @todo Notaus bei fehlerhaften Antworten des XpressNet-Interface
 */

#include "xpressnet.h"
#include "util.h"
#include "xpressnet_shared_memory.h"
#include "rs232_shared_memory.h"

/**
 * @name Fahrgeschwindigkeiten
 *
 * Experimentell ermittelte Fahrgeschwindigkeiten. Es gibt 128 Fahrstufen
 * (0x00 bis  0x7F), das MSB (0x80) gibt die Fahrtrichtung an (0x80 = vorwärts,
 * 0x00 = rückwärts).
 *
 * @todo Validieren der Geschwindigkeiten, experimentelle Bestätigung.
 */
/*@{*/
#define V_STOP 0x00
#define V_ABKUPPELN 0x88
#define V_ANKUPPELN 0x1F
#define V_FAHRT 0xDD
/*@}*/

/**
*
* @name Xpressnet-Addressen
*
* Adressen siehe Pflichtenheft -> Adresszuordnung.
*
* @attention Die Adressen für <b>Weichen</b> und <b>Entkuppler</b> werden
* auf der Multimaus (und im Pflichtenheft) von 1-1024 vergeben, auf dem
* Xpressnet-Bus jedoch von 0-1023 angesprochen.
* Die Adresse 0 entspricht also der Adresse 1 auf der Multimaus, die Adresse
* 2 der Adresse 3 auf der Multimaus.
*/
/*@{*/
#define XPRESSNET_LOK_1 0x01
#define XPRESSNET_LOK_2 0x02
#define XPRESSNET_WEICHE_A 0x03
#define XPRESSNET_WEICHE_B 0x04
#define XPRESSNET_WEICHE_C 0x02
#define XPRESSNET_ENTKUPPLER_E1 0x06
#define XPRESSNET_ENTKUPPLER_E2 0x05
/*@}*/


/**
 * @name Funktionen zur Befehlsabarbeitung
 *
 * Diese Funktionen lesen die Befehle aus dem Shared Memory ein
 * ( @link xpressnet_shared_memory::streckenbefehl_xpressnet
 * streckenbefehl_xpressnet @endlink ) und starten die Verarbeitung.
 */
 /*@{*/
static void checkForInput();
static void checkForCommands();
static void commandWeiche();
static void commandEntkuppler();
static void commandLok();
/*@}*/


/**
 * @name XpressNet-Codierung
 *
 * Funktionen zur Konvertierung von XpressNet-Befehlen
 * (siehe xpressnet_li101f.pdf, 3.24 und 3.26)
 *
 */
/*@{*/
static bool writeSchaltbefehl(uint8_t address, uint8_t output, bool activate);
static bool writeFahrbefehl(uint8_t address, uint8_t speed);
/*@}*/

/**
 * @name Funktionen zum Lesen und Schreiben der RS232-Ringbuffer
 */
/*@{*/
static uint8_t write_byte(uint8_t b);
static uint8_t max_bytes_to_write();
static uint8_t bytes_to_read();
static uint8_t read_byte();
static uint8_t peek_byte();
/*@}*/

/**
 * @name Lokale Variablen
 */
/*@{*/
 /**
 * @brief Warten auf Befehlsbestätigung vom LI101F
 *
 * Nach dem jedem Befehl sollte die Zentrale eine Quittierung senden. Ausnahme
 * ist der zweite Befehl (Aktivierung) bei Entkupplern.
 */
static bool wait_for_answer = TRUE;
 /**
 * @brief Warten auf Schaltinformation vom LI101F
 *
 * Nach dem zweiten Befehl (Aktivierung) bei Weichen und Entkupplern kommt diese
 * Rückmeldung. Bei Entkupplern ist dies an der Stelle auch die einzige
 * Rückmeldung.
 */
static bool wait_for_schaltinformation = TRUE;
/**
 * @brief Der aktuelle Befehl ist der Deaktivierungsbefehl, die Aktivierung
 * muss noch gesendet werden
 */
static bool activation_pending = FALSE;
/*@}*/





/**
 * @brief XpressNet Initialisierung
 *
 * Initialisiert XpressNet.
 *
 * @pre RS232 muss bereits initialisiert sein.
 */
void xpressnet_init ()
{
    wait_for_answer = FALSE;
    wait_for_schaltinformation = FALSE;
}

/**
 * @brief XpressNet Work-Funktion
 *
 * Verarbeitet zu sendende Streckenbefehle und wertet Antworten vom
 * Xpressnet-Interface aus.
 */
void xpressnet_work()
{
    // Anworten auswerten
    checkForInput();

    // Antwort erhalten? Neue Befehle ausführen
    if(!wait_for_answer && !wait_for_schaltinformation) {
        checkForCommands();
    }
}

/**
 * @brief Startet die Streckenbefehlverarbeitung.
 *
 * Prüft, ob ein Streckenbefehl vorliegt, und ruft die Funktionen zur
 * Verarbeitung der Befehle auf.
 * @sa commandLok
 * @sa commandWeiche
 * @sa commandEntkuppler
 */
static void checkForCommands()
{
    if(streckenbefehl_xpressnet.target != IDLE)
    {
        commandLok();
        commandWeiche();
        commandEntkuppler();
    }
}

/**
 * @brief Führt einen einen Lokbefehl durch, wenn gesetzt.
 *
 * Prüft, ob eine Lok angesteuert werden soll, und sendet den notwendigen
 * Fahrbefehl.
 *
 * @sa writeFahrbefehl
 */
static void commandLok()
{
    uint8_t xpressnet_address = 0, speed = 0;

    // XpressNet-Adresse bestimmen
    switch(streckenbefehl_xpressnet.target)
    {
    case LOK_RED:
        xpressnet_address = XPRESSNET_LOK_1;
        break;
    case LOK_BLACK:
        xpressnet_address = XPRESSNET_LOK_2;
        break;
    default:
        // Keine Lok
        return;
    }

    switch(streckenbefehl_xpressnet.command)
    {
    case 0x00:
        speed = V_STOP;
        break;
    case 0x01:
        speed = V_ABKUPPELN;
        break;
    case 0x02:
        speed = V_ANKUPPELN;
        break;
    case 0x03:
        speed = V_FAHRT;
        break;
    default:
        // Ungültiger Befehl
        return;
    }

    if(!writeFahrbefehl(xpressnet_address, speed))
    {
        // TODO: FEHLER;
        return;
    }

    // Lokbefehl wird von Zentrale quittiert
    wait_for_answer = TRUE;
}

/**
 * @brief Führt einen einen Enkupplerbefehl durch, wenn gesetzt.
 *
 * Prüft, ob ein Enkuppler gesetzt werden soll, und sendet nacheinander die
 * beiden notwendigen Schaltbefehle.
 *
 * @sa writeSchaltbefehl
 */
static void commandEntkuppler() {
    uint8_t xpressnet_address = 0;

    // XpressNet-Adresse bestimmen
    switch(streckenbefehl_xpressnet.target)
    {
    case ENTKUPPLER_E1:
        xpressnet_address = XPRESSNET_ENTKUPPLER_E1;
        break;
    case ENTKUPPLER_E2:
        xpressnet_address = XPRESSNET_ENTKUPPLER_E2;
        break;
    default:
        // Kein Entkuppler
        return;
    }

    if(!activation_pending) {
        // Entkuppler erst deaktivieren
        if(!writeSchaltbefehl(xpressnet_address, 0, FALSE))
        {
            // TODO: FEHLER;
            return;
        }

        // 1. Schaltbefehl wird von Zentrale quittiert
        wait_for_answer = TRUE;
        activation_pending = TRUE;
    }
    else {
        // Entkuppler aktivieren
        if(!writeSchaltbefehl(xpressnet_address, 0, TRUE))
        {
            // TODO: FEHLER;
            return;
        }

        // 2. Schaltbefehl wird NICHT von Zentrale quittiert, nur mit
        // Schaltinformation
        wait_for_schaltinformation = TRUE;
        activation_pending = FALSE;
    }
}

/**
 * @brief Führt einen einen Weichenbefehl durch, wenn gesetzt.
 *
 * Prüft, ob eine Weiche gesetzt werden soll, und sendet nacheinander die beiden
 * notwendigen Schaltbefehle.
 *
 * @sa writeSchaltbefehl
 */
static void commandWeiche() {
    uint8_t xpressnet_address = 0;

    // XpressNet-Adresse bestimmen
    switch(streckenbefehl_xpressnet.target)
    {
    case WEICHE_A:
        xpressnet_address = XPRESSNET_WEICHE_A;
        break;
    case WEICHE_B:
        xpressnet_address = XPRESSNET_WEICHE_B;
        break;
    case WEICHE_C:
        xpressnet_address = XPRESSNET_WEICHE_C;
        break;
    default:
        // Keine Weiche
        return;
    }

    if(!activation_pending) {
        // Weiche erst in der anderen Richtung deaktivieren
        if(!writeSchaltbefehl(xpressnet_address, streckenbefehl_xpressnet.command, FALSE))
        {
            // TODO: FEHLER;
            return;
        }

        // 1. Schaltbefehl wird von Zentrale quittiert
        wait_for_answer = TRUE;
        activation_pending = TRUE;
    }
    else {
        // Weiche in der gewünschten Richtung aktivieren
        if(!writeSchaltbefehl(xpressnet_address, 1-streckenbefehl_xpressnet.command, TRUE))
        {
            // TODO: FEHLER;
            return;
        }

        // 2. Schaltbefehl wird von Zentrale UND mit Schaltinformation
        // quittiert
        wait_for_answer = TRUE;
        wait_for_schaltinformation = TRUE;
        activation_pending = FALSE;
    }
}

/**
 * @brief Wertet die Antworten vom Xpressnet-Interface aus.
 *
 * Bei einer Befehlsbestätigung wird der Streckenbefehl zurückgesetzt. Tritt ein
 * Kommunikationsfehler auf, wird der Notaus ausgelöst.
 *
 */
static void checkForInput()
{
    uint8_t retval;

    if(bytes_to_read() > 0)
    {
        switch(peek_byte())
        {
        case 0x01:
            // 0x01: Antwort auf einen Befehl
            if(bytes_to_read() >= 3) {
                // Headerbyte lesen
                read_byte();
                retval = read_byte();
                // Checksummen-Prüfung: 3. Byte ist XOR der ersten beiden
                if((retval ^ 0x01) != read_byte()) {
                    // TODO: FEHLER: Falsche Checksumme
                    return;
                }
                switch(retval) {
                /**
                 @todo Funktion bei Timeout - so nicht sinnvoll

                case 0x01:
                    // Timeout
                    wait_for_answer = FALSE;
                    wait_for_schaltinformation = FALSE;
                    if(activation_pending)
                    {
                        activation_pending = FALSE;
                    }
                    break;
                */
                case 0x04:
                    // Alles ok
                    wait_for_answer = FALSE;
                    if(!activation_pending && !wait_for_schaltinformation) {
                        // Nach erfolgter Aktivierung Streckenbefehl löschen
                        streckenbefehl_xpressnet.target = IDLE;
                    }
                    break;
                /**
                 @todo Funktion bei Überlauf - so nicht sinnvoll

                case 0x06:
                    // Überlauf
                    wait_for_answer = FALSE;
                    wait_for_schaltinformation = FALSE;
                    if(activation_pending)
                    {
                        activation_pending = FALSE;
                    }
                    break;
                */
                /**
                 @todo Funktion bei anderen Fehlern - so nicht sinnvoll

                default:
                    wait_for_answer = FALSE;
                    break;
                    // TODO: Kommunikationsfehler: NOTAUS
                */
                }
            }
            break;
        case 0x42:
            // 0x42: Schaltinformation
            if(bytes_to_read() >= 4) {
                // Checksummen-Prüfung: 4. Byte ist XOR der ersten drei
                if((read_byte() ^ read_byte() ^ read_byte()) != read_byte()) {
                    // TODO: FEHLER: Falsche Checksumme
                    return;
                }
                // Alles ok
                wait_for_schaltinformation = FALSE;
                if(!activation_pending && !wait_for_answer) {
                    // Nach erfolgter Aktivierung Streckenbefehl löschen
                    streckenbefehl_xpressnet.target = IDLE;
                }
            }
            break;
        default:
            read_byte();
            /**
             * @todo Auswertung der Rückmeldung korrekt implementieren (Länge
             * des Befehls auswerten, andere Antworten und ungefragte
             * Informationen auswerten etc.)
             */
        }
    }
}



 /**
 * @brief Schreibt einen Schaltbefehl für Weichen oder Entkuppler.
 *
 * @param address  Die Xpressnet-Adresse des Schaltempfängers.
 * @param output   Der zu setztende Ausgang (bei Entkupplern immer 0, bei
 *                 Weichen 0 = Abbiegen, 1 = Geradeaus).
 * @param activate true, wenn der gewählte Ausgang aktiviert werden soll, sonst
 *                 false.
 * @return Gibt true zurück, wenn der Befehl erfolgreich in den RS232-Ringbuffer
 *         geschrieben werden konnte, sonst false.
 *
 * @sa rs232_shared_memory.h
 */
static bool writeSchaltbefehl(uint8_t address, uint8_t output, bool activate) {
    uint8_t xor_byte=0;

    // Vier Byte müssen für die Nachricht frei sein
    if(max_bytes_to_write() < 4)
    {
        return FALSE;
    }

    // Header
    xor_byte ^= write_byte(0x52);
    // Address-Gruppe (Adresse / 4), die letzten zwei Bit stehen im nächsten Byte
    xor_byte ^= write_byte(address >> 2);

    if(activate) {
        xor_byte ^= write_byte(
        0x88 |                          // Aktivierungsbefehl
        (address & 0x03) << 1 |         // die beiden Address-LSB
        output);                        // der Ausgang des Schaltempfängers
    }
    else {
        xor_byte ^= write_byte(
        0x80 |                          // Deaktivierungsbefehl
        (address & 0x03) << 1    |      // die beiden Address-LSB
        output);                        // der Ausgang des Schaltempfängers
    }

    write_byte(xor_byte);

    return TRUE;
}

 /**
 * @brief Schreibt einen Fahrbefehl für eine Lok.
 *
 * @param address  Die Xpressnet-Adresse der Lok.
 * @param speed    Die Geschwindigkeit
 * @return Gibt true zurück, wenn der Befehl erfolgreich in den RS232-Ringbuffer
 *         geschrieben werden konnte, sonst false.
 *
 * @sa rs232_shared_memory.h
 */
static bool writeFahrbefehl(uint8_t address, uint8_t speed) {
    uint8_t xor_byte=0;

    // Sechs Byte müssen für die Nachricht frei sein
    if(max_bytes_to_write() < 6)
    {
        return FALSE;
    }

    // Header
    xor_byte ^= write_byte(0xE4);
    // Header für 128-stufige Geschwindigkeiten
    xor_byte ^= write_byte(0x13);
    // Adresse High (immer 0)
    xor_byte ^= write_byte(0x00);
    // Adresse Low
    xor_byte ^= write_byte(address);

    // Geschwindigkeit
    xor_byte ^= write_byte(speed);

    write_byte(xor_byte);

    return TRUE;
}


/**
 * @brief Schreibt ein Byte in den Ausgabepuffer des RS232-Treibers.
 * @param b Das zu schreibende Byte.
 * @return Das geschriebene Byte.
 */
static uint8_t write_byte(uint8_t b) {
    rs232_output_buffer[rs232_output_write_pos] = b;
    rs232_output_write_pos = (rs232_output_write_pos + 1) % RS232_BUFFERSIZE;
    return b;
}

/**
 * @brief Gibt die Anzahl der freien Byte im Ausgabepuffer des RS232-Treibers
 *        zurück .
 * @return Die Anzahl der freien Bytes.
 */
static uint8_t max_bytes_to_write() {
    return (rs232_output_read_pos + RS232_BUFFERSIZE -
            rs232_output_write_pos - 1) % RS232_BUFFERSIZE;
}

/**
 * @brief Gibt die Anzahl vorhandenen Bytes im Eingabepuffer des RS232-Treibers
 *        zurück.
 * @return Die Anzahl der zu lesenden Bytes.
 */
static uint8_t bytes_to_read() {
    return (rs232_input_write_pos + RS232_BUFFERSIZE -
            rs232_input_read_pos) % RS232_BUFFERSIZE;
}

/**
 * @brief Liest ein Byte aus dem Eingabepuffer des RS232-Treibers, und entfernt
 *        es aus dem Puffer.
 * @return Das gelesene Byte.
 */
static uint8_t read_byte() {
    uint8_t inp;
    inp = rs232_input_buffer[rs232_input_read_pos];
    rs232_input_read_pos = (rs232_input_read_pos + 1) % RS232_BUFFERSIZE;
    return inp;
}

/**
 * @brief Liest ein Byte aus dem Eingabepuffer des RS232-Treibers, ohne es
          aus dem Puffer zu entfernen.
 * @return Das gelesene Byte.
 */
static uint8_t peek_byte() {
    return rs232_input_buffer[rs232_input_read_pos];
}
