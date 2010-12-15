/**
 * @file
 * @ingroup xpressnet_rs232
 * @brief XpressNet-Treiber
 *
 * Sendet XpressNet-Befehle aus dem Shared Memory in der Work-Funktion und 
 * wertet die Antworten aus.
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 * @sa xpressnet.c
 */

#ifndef _XPRESSNET_H_
#define _XPRESSNET_H_
 
#include "types.h"
#include "xpressnet_shared_memory.h"

void xpressnet_init ();
   
void xpressnet_work();

#endif