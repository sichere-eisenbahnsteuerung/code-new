/**
* @file rs232.h
* @brief RS232 driver
*
* Hardware driver for RS232 port. Serial port receive data is read into a ringbuffer via interrupt. 
* Data to be sent is saved in a ringbuffer and will be sent when RS232_work is called.
*/

#ifndef _RS232_H_
#define _RS232_H_
 
#include "../common/types.h"
#include "../betriebsmittel/rs232_shared_memory.h"
  
/**
 * @brief RS232 init function
 *
 * Init the RS232 port.
 */
void RS232_init ();
         
     
/**
 * @brief RS232 receive function
 *
 * Reads all available bytes from the receive buffer.
 *
 * @param buffer Provided buffer to store bytes.
 * @return the next byte, or NULL if no byte available
 */   
uint8_t RS232_read();


#endif