/*
 *    RS232-Treiber
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
 
//extern T1, R1, SBUF;
#include "types.h"
#include "c515c.h"
#include "rs232.h"
#include "rs232_win_linux.h"
#include "util.h"

/**
 * @name Lokale Variablen
 */
/*@{*/
 /**
 * @brief Der zu nutzende COM-Port.
 */
static int Comport = 13; // COM14
/*@}*/


/**
 * @brief RS232 Initialisierung.
 *
 * Initialisiert die RS232 Hardware und leert das Shared Memory.
 */
void rs232_init ()
{
    CTS_PIN = 1;
    OpenComport(0, "\\\\.\\COM1", 19200);
}

/**
 * @brief RS232 Work-Funktion.
 *
 * Sendet alle Bytes aus dem Sendepuffer, solange CTS gesetzt ist.
 */
void rs232_work()
{
    uint8_t inp=0;
    // Solange CTS gesetzt ist und noch Zeichen zu senden sind
    while(CTS_PIN && rs232_output_read_pos != rs232_output_write_pos) {
        // Zeichen senden
        SBUF = rs232_output_buffer[rs232_output_read_pos];
        rs232_output_read_pos = (rs232_output_read_pos + 1) % RS232_BUFFERSIZE;
        printf("SEROUT: 0x%X\n", SBUF);
        SendByte(0, SBUF);
    }
    // Solange CTS gesetzt ist und noch Zeichen zu senden sind
    while(PollComport(0, &inp, 1) > 0) {
        printf("SERIN: 0x%X\n", inp);
        if((rs232_input_write_pos+1) % RS232_BUFFERSIZE != rs232_input_read_pos)
        {
            rs232_input_buffer[rs232_input_write_pos] = inp;
            rs232_input_write_pos = (rs232_input_write_pos + 1) % RS232_BUFFERSIZE;
        }
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
    }
    enable_interrupts(TRUE);
}
/*@}*/
