/**
* @file xpressnet.h
* @brief RS232 driver
*
* XpressNet Treiber. Sendet XpressNet-Befehle aus dem Shared Memory in der Work-Funktion und wertet die Antwort aus. Dabei wird der RS232-Treiber genutzt und selbststaendig aufgerufen.
*/

#ifndef _XPRESSNET_H_
#define _XPRESSNET_H_
 
#include "types.h"
  
/**
 * @brief XpressNet Initialisierung
 *
 * Initialisiert XpressNet und RS232.
 */
void xpressnet_init ();

/**
 * @brief XpressNet Work-Funktion
 *
 * Ruft auch die RS232 Work-Funktion auf.
 */       
void xpressnet_work();


#endif