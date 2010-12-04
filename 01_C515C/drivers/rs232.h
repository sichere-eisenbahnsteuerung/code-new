/**
* @file rs232.h
* @brief rs232 driver
*
* Hardware driver for rs232 port. Serial port receive data is read into a ringbuffer via interrupt. 
* Data to be sent is saved in a ringbuffer and will be sent when rs232_work is called.
*/

#ifndef _RS232_H_
#define _RS232_H_
 
#include "types.h"
  
/**
 * @brief rs232 init function
 *
 * Init the rs232 port.
 */
void rs232_init();
      
void rs232_work();


#endif