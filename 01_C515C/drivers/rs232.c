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
 * @brief RS232 Initialisierung.
 *
 * Initialisiert die RS232 Hardware und leert das Shared Memory.
 */
void rs232_init ()
{
    // Baudratengenerator einschalten
    BD = 1;
    // Mode 1  8Bit variable Baudrate
    SM0 = 0;
    SM1 = 1;
    // 9600 Baud
    SRELH = 0x03;
    SRELL = 0xDF;
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
