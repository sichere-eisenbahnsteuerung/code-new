/**
 * @file
 * @ingroup sharedmemory
 * @ingroup xpressnet_rs232
 * @brief Shared Memory Deklarationen des Xpressnet-Treibers
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 */
 
#ifndef _XPRESSNET_SHARED_MEMORY_H_
#define _XPRESSNET_SHARED_MEMORY_H_

#include "types.h"

/** @brief Der zu sendende Streckenbefehl. 
 *
 * Wurde der Befehl erfolgreich gesendet, wird das Ziel auf IDLE gesetzt. 
 */
extern streckenbefehl streckenbefehl_xpressnet;

#endif