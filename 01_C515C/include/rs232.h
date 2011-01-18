/*
 *    rs232 Header
 *    Copyright (C) 2011 Hochschule Bremen
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
