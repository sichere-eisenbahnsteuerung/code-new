/**
 * @file
 * @ingroup xpressnet_rs232
 * @brief RS232-Treiber
 *
 * Bytes aus dem Ringbuffer im Shared Memory werden in der Work-Funktion gesendet, per Interrupt empfangene Bytes in einen zweiten Ringbuffer geschrieben.
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 *
 * @sa rs232.c
 */

#ifndef _RS232_H_
#define _RS232_H_

#include "rs232_shared_memory.h"

#include "types.h"

/**
 * @brief Hardware-Pin für das CTS-Signal.
 *
 * Das CTS-Signal liegt Hardwareseitig auf dem Anschluss T1. Zur Kompatibilität 
 * mit dem Testframework wird nicht die Portnotation (z.B. P3^4) verwendet.
 */
#define CTS_PIN T1

void rs232_init ();
void rs232_work();


#endif
