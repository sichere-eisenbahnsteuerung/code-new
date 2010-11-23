#ifndef _RS232_SHARED_MEMORY_H_
#define _RS232_SHARED_MEMORY_H_

#define RS232_BUFFERSIZE 20

extern uint8_t rs232_input_buffer[RS232_BUFFERSIZE];  
extern uint8_t rs232_input_read_pos;          
extern uint8_t rs232_input_write_pos;            

extern uint8_t rs232_output_buffer[RS232_BUFFERSIZE];
extern uint8_t rs232_output_read_pos;          
extern uint8_t rs232_output_write_pos;

#endif