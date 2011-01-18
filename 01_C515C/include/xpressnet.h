/*
 *    XpressNet-Treiber
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
