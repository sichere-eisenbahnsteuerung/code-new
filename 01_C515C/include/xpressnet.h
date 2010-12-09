/**
 * @file
 * @ingroup xpressnet_rs232
 * @brief XpressNet-Treiber
 *
 * Sendet XpressNet-Befehle aus dem Shared Memory in der Work-Funktion und wertet die Antwort aus. Dabei wird der RS232-Treiber genutzt und selbststaendig  aufgerufen.
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 */

#ifndef _XPRESSNET_H_
#define _XPRESSNET_H_
 
#include "types.h"
#include "xpressnet_shared_memory.h"
  
/**
 * @brief XpressNet Initialisierung
 *
 * Initialisiert XpressNet.
 * 
 * @pre RS232 muss bereits initialisiert sein.
 */
void xpressnet_init ();

/**
 * @brief XpressNet Work-Funktion
 */       
void xpressnet_work();


#endif