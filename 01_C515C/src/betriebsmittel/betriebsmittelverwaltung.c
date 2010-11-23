#include "../common/types.h"
#include "rs232_shared_memory.h"


/* 
 * Shared Memory RS232 
 */

uint8_t rs232_input_buffer[RS232_BUFFERSIZE] = {0};  
uint8_t rs232_input_read_pos = 0;          
uint8_t rs232_input_write_pos = 0;            

uint8_t rs232_output_buffer[RS232_BUFFERSIZE] = {0};
uint8_t rs232_output_read_pos = 0;          
uint8_t rs232_output_write_pos = 0;