/**
* @file rs232.h
* @brief RS232 driver
*
* Hardware driver for RS232 port. Serial port receive data is read into the provided ringbuffer via interrupt. Data is sent immediately.
*/

#ifndef _RS232_H_
#define _RS232_H_
 
#include "../common/types.h"
#include "../common/ringbuffer.h"


  
/**
 * @brief RS232 init function
 *
 * Init the RS232 port.
 */
void RS232_init ();
       
/**
 * @brief RS232 send function
 *
 * Send single byte via RS232.
 *
 * @param c The byte to send.
 */
void RS232_send(uint8_t c);     

 
/**
 * @brief RS232 receive function
 *
 * Reads all available bytes from the receive buffer.
 *
 * @param buffer Provided buffer to store bytes.
 * @param length Length of the provided buffer.
 */   
uint8_t RS232_read(uint8_t *buffer, uint8_t length);

#endif