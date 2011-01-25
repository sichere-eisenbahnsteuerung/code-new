/*
 *    RS232-Treiber
 *    Copyright (C) 2011  Hanno Fellmann
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
 * @brief RS232-Treiber
 *
 * Bytes aus dem Ringbuffer im Shared Memory werden in der Work-Funktion
 * gesendet, per Interrupt empfangene Bytes in einen zweiten
 * Ringbuffer geschrieben.
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 */
		 
#include "types.h"
#include "rs232.h"
#include "c515c.h"
#include "util.h"

/**
 * @name Lokale Variablen
 */
/*@{*/
 /**
 * @brief Warten auf erfolgreiches Senden des letzten Zeichens
 */
static bool wait_for_send = TRUE;
/*@}*/

/**
 * @brief Baudrate: 19200 Baud
 */
#define BAUDRATE 19200L
/**
 * @brief Wert des Registers SMOD
 */
#define SMOD 0
/** 
 * @brief Reload-Werte für den Baudraten-Generator
 *
 * Der Baudraten-Generator ist ein 10-Bit Timer, der im
 * Gegensatz zu den Standard-Timern mit dem Quarztakt zählt.
 * Der Overflow des Baudraten-Generators ist die Baud-Rate-Clock,
 * deren Taktfrequenz das 16-fache der Baudrate ist.
 *
 * Mit der Formel 1024 - (2 x Quarztakt) / (32 x Baudrate) lässt
 * sich der Reload-Wert berechnen, der beim Overflow des 
 * Baudraten-Generators automatisch wieder geladen werden muss
 * (siehe auch C515C-Manual).
 *
 * Der 16-Bit Wert wird auf SRELH und SRELL aufgeteilt.
 */
#define SERIAL_RELOAD 1024L - ((SMOD ? 2 : 1) * QUARZTAKT) / (32 * BAUDRATE)

/**
 * @brief RS232 Initialisierung.
 *
 * Initialisiert die RS232 Hardware und leert das Shared Memory.
 */
void rs232_init ()
{
	// CTS als Input konfigurieren
	CTS_PIN = 1;
	// Baudratengenerator einschalten
    BD = 1;
    // Mode 1 -> 8 Bit, variable Baudrate
    SM0 = 0;
    SM1 = 1;
    // Baudrate setzen (mit SMOD = 1)
	SRELH = (SERIAL_RELOAD >> 8); 
	SRELL = SERIAL_RELOAD & 0xFF;
    // seriellen Empfang einschalten
    REN = 1;
    TI = 1;
    // Enable serial interrupts
    ES = 1;

    rs232_output_read_pos = rs232_output_write_pos = 0;
    rs232_input_read_pos = rs232_input_write_pos = 0;
    wait_for_send = FALSE;
}

/**
 * @brief RS232 Work-Funktion.
 *
 * Sendet alle Bytes aus dem Sendepuffer, solange CTS gesetzt ist.
 */
void rs232_work()
{  
    // Solange CTS gesetzt ist und noch Zeichen zu senden sind
    while(CTS_PIN && rs232_output_read_pos != rs232_output_write_pos) {
        // Auf das Senden des lezten Zeichens warten
        WAIT_FOR(wait_for_send == FALSE);
        wait_for_send = TRUE;
        // Zeichen senden
        SBUF = rs232_output_buffer[rs232_output_read_pos];
        rs232_output_read_pos = (rs232_output_read_pos + 1) % RS232_BUFFERSIZE;
    }
}

/**
 * @name Interrupt-Routinen
 */
/*@{*/
/**
 * @brief Serielle Interrupt-Routine.
 *
 * Wird vom Mikrocontroller aufgerufen, wenn ein Zeichen empfangen wurde
 * (RI-Flag gesetzt), oder das Senden eines Zeichens (TI-Flag gesetzt)
 * abgeschlossen ist.
 */
void rs232_interrupt(void) INTERRUPT(4)
{
    enable_interrupts(FALSE);
    if(RI)
    {
        // Zeichen empfangen und in den Empfangsbuffer schreiben
        if((rs232_input_write_pos+1) % RS232_BUFFERSIZE != rs232_input_read_pos)
        {
            rs232_input_buffer[rs232_input_write_pos] = SBUF;
            rs232_input_write_pos = (rs232_input_write_pos + 1) % RS232_BUFFERSIZE;
        }
        RI = 0;
    }
    if(TI)
    {
        // Zeichen wurde gesendet, nicht mehr auf erfolgreiches Senden warten.
        TI = 0;
        wait_for_send = FALSE;
    }
    enable_interrupts(TRUE);
}
/*@}*/
