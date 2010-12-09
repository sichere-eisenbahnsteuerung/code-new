#include "rs232.h"
#include "c515c.h"
#include "util.h"		

static volatile uint8_t input_byte = 0;
static bool wait_for_send = TRUE;

void rs232_init ()
{    
    BD = 1; 					// Baudratengenerator einschalten
	SM0 = 0; 					// Mode 1  8Bit variable Baudrate
	SM1 = 1;
	SRELH = 0x03; 				// 9600 Baud
	SRELL = 0xDF;
	REN = 1; 					// seriellen Empfang einschalten
	TI = 1;
    ES = 1;                     // Enable serial interrupts
    
	rs232_output_read_pos = rs232_output_write_pos = 0;
	rs232_input_read_pos = rs232_input_write_pos = 0;
    wait_for_send = FALSE;
}

void rs232_work()  
{	
	while(CTS_PIN && rs232_output_read_pos != rs232_output_write_pos) {		   				// Solange CTS gesetzt ist und noch Zeichen zu senden sind
		WAIT_FOR(wait_for_send == FALSE); // Auf das Senden des lezten Zeichens warten
        wait_for_send = TRUE;
        SBUF = rs232_output_buffer[rs232_output_read_pos];									// Zeichen senden
        rs232_output_read_pos = (rs232_output_read_pos + 1) % RS232_BUFFERSIZE;
	}
}

void rs232_interrupt(void) INTERRUPT(4)
{
    enable_interrupts(FALSE);
    if(RI)
    {    
        if((rs232_input_write_pos+1) % RS232_BUFFERSIZE != rs232_input_read_pos) 
        {
            rs232_input_buffer[rs232_input_write_pos] = SBUF;
            rs232_input_write_pos = (rs232_input_write_pos + 1) % RS232_BUFFERSIZE;
        }
        RI = 0;    
    }
    if(TI)
    {
        TI = 0;
        wait_for_send = FALSE;
    }
    enable_interrupts(TRUE);
}          
 
