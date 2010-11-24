                       
#include <intrins.h>
#include "main.h"
#include "common/util.h"

#include "drivers/rs232.h"

/*
 * @brief Initialize common stuff for the main program
 */
void init_common(void)
{
	enable_interrupts(1);
    RS232_init();
}

/*
 * @brief The method which gets called initialy by the processor
 */
void main()
{
    uint8_t inp=0;

	init_common();

    rs232_output_buffer[rs232_output_write_pos] = 't';
    rs232_output_write_pos = (rs232_input_write_pos + 1) % RS232_BUFFERSIZE;

    while(1) {
        RS232_work();
        if(rs232_input_read_pos != rs232_input_write_pos) 
        {
            inp = rs232_input_buffer[rs232_input_read_pos];
            rs232_input_read_pos = (rs232_input_read_pos + 1) % RS232_BUFFERSIZE;

            rs232_output_buffer[rs232_output_write_pos] = inp;
            rs232_output_write_pos = (rs232_output_write_pos + 1) % RS232_BUFFERSIZE;
        }
    }
}
