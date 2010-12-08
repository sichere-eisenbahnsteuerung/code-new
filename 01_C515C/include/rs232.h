/**
 * @file
 * @ingroup xpressnet_rs232
 * @brief RS232-Treiber
 *
 * Bytes aus dem Ringbuffer im Shared Memory werden in der Work-Funktion gesendet, per Interrupt empfangene Bytes in einen zweiten Ringbuffer geschrieben.
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 */

#ifndef _RS232_H_
#define _RS232_H_
 
#include "rs232_shared_memory.h"
  
#include "types.h"

/**
 * @brief Hardware-Pin für das CTS-Signal
 */
#define CTS_PIN T1     

/**
 * @brief RS232 Initialisierung
 */
void rs232_init ();

/**
 * @brief RS232 Work-Funktion
 */      
void rs232_work();


#endif
