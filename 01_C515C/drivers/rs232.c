#include "rs232.h"
#include <REG515C.H>
#include "util.h"

static volatile uint8_t input_byte = 0;
static char wait_for_send = 1;
    

void RS232_init ()
{    
    BD = 1; // Baudratengenerator einschalten
	SM0 = 0; // Mode 1  8Bit variable Baudrate
	SM1 = 1;
	SRELH = 0x03; // 9600 Baud
	SRELL = 0xDF;
	REN = 1; // seriellen Empfang einschalten
	TI = 1;
//
//    SCON  = 0x50;                   /* SCON: mode 1, 8-bit UART, enable rcvr    */
//    TMOD |= 0x20;                   /* TMOD: timer 1, mode 2, 8-bit reload      */
//    TH1   = 0xf3;                   /* TH1:  reload value for 2400 baud         */
//    TR1   = 1;                      /* TR1:  timer 1 run                        */
//    TI    = 1;                      /* TI:   set TI to send first char of UART  */
//    
    ES = 1;                         /* Enable serial interrupts */
    
    wait_for_send = 0;
}

void RS232_work()  {
    if(!wait_for_send) 
    {   
        if(rs232_output_read_pos != rs232_output_write_pos) 
        {
            wait_for_send = 1;
            SBUF = rs232_output_buffer[rs232_output_read_pos];
            rs232_output_read_pos = (rs232_output_read_pos + 1) % RS232_BUFFERSIZE;
        }
    }
}

void RS232_interrupt(void) interrupt 4 {
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
        wait_for_send = 0;
    }
    enable_interrupts(TRUE);
}          
 