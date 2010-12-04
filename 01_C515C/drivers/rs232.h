/**
* @file rs232.h
* @brief RS232 Treiber
*
* Hardware Treiber für RS232. Bytes aus dem Ringbuffer im Shared Memory werden in der Work-Funktion gesendet, per Interrupt empfangene Bytes in einen zweiten Ringbuffer geschrieben.
*/

#ifndef _RS232_H_
#define _RS232_H_
 
#include "types.h"
  
/**
 * @brief RS232 Initialisierung
 */
void rs232_init();

/**
 * @brief RS232 Work-Funktion
 */      
void rs232_work();


#endif