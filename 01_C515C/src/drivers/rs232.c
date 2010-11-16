#include "rs232.h"
#include <REG515C.H>
#include "../common/util.h"

static volatile uint8_t input_byte = 0;
static char wait_for_send = 1;

static ringbuffer_t input_buffer, output_buffer;
    

void RS232_init ()
{    
    ringbuffer_init(&input_buffer);
    
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

bool RS232_write(uint8_t c)  {
   return ringbuffer_write(&output_buffer, c);
}

void RS232_work()  {
    if(!wait_for_send) 
    {   
        if(!ringbuffer_empty(&output_buffer)) 
        {
            wait_for_send = 1;
            SBUF = ringbuffer_read(&output_buffer);
        }
    }
}

uint8_t RS232_read() {
    return ringbuffer_read(&input_buffer);
}      

bool RS232_available() {
    return !ringbuffer_empty(&input_buffer);
}

void RS232_interrupt(void) interrupt 4 {
    enable_interrupts(FALSE);
    if(RI)
    {    
        ringbuffer_write(&input_buffer, SBUF);
        RI = 0;    
    }
    if(TI)
    {
        TI = 0;
        wait_for_send = 0;
    }
    enable_interrupts(TRUE);
}          
 