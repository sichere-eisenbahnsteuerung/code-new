#include "rs232.h"
#include <REG515C.H>
#include "../common/util.h"

volatile uint8_t input_byte = 0;
char wait_for_send = 0;

ringbuffer_t input_buffer;
    

void RS232_init ()
{    
    ringbuffer_init(&input_buffer);

    SCON  = 0x50;                   /* SCON: mode 1, 8-bit UART, enable rcvr    */
    TMOD |= 0x20;                   /* TMOD: timer 1, mode 2, 8-bit reload      */
    TH1   = 0xf3;                   /* TH1:  reload value for 2400 baud         */
    TR1   = 1;                      /* TR1:  timer 1 run                        */
    TI    = 1;                      /* TI:   set TI to send first char of UART  */
    
    ES = 1;                         /* Enable serial interrupts */
    
    wait_for_send = 0;
}

void RS232_send(uint8_t c)  {
    while(wait_for_send) 
    {
        // Wait for Transmit Interrupt
    }
    wait_for_send = 1;
    SBUF = c;
}

uint8_t RS232_read(uint8_t *buffer, uint8_t length) {
    uint8_t pos=0, input;
    while(pos < length && ringbuffer_read(&input_buffer, &input))
    {
        buffer[pos] = input;
        pos++;
    }
    return pos;
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
    enable_interrupts(FALSE);
}          
