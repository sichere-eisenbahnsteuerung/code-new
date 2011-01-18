/*
 *    Shared Memory Deklarationen des Xpressnet-Treibers
 *    Copyright (C) 2011 Hanno Fellmann
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
