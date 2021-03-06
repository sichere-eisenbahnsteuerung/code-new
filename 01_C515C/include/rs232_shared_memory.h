/*
 *    RS232 shared memory Header
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
 * @ingroup sharedmemory
 * @ingroup xpressnet_rs232
 * @brief Shared Memory Deklarationen des RS232 Treibers.
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 */
 
#ifndef _RS232_SHARED_MEMORY_H_
#define _RS232_SHARED_MEMORY_H_

#include "types.h"

/**
 * @brief Gr��e der Ringbuffer in Bytes
 *
 * Die Gr��e des RS232-Buffers betr�gt 20 Bytes, da die maximale L�nge eines
 * Xpressnet-Befehls 17 Byte betr�gt, und ein gewisser Puffer f�r die Dauer der
 * Abarbeitung ber�cksichtigt werden muss.
 */
#define RS232_BUFFERSIZE 20

/**
 * @name Puffer f�r empfangene Zeichen
 * In diesem Ringpuffer werden empfangene Zeichen abgelegt.
 */
/*@{*/
/** @brief Empfangs-Ringbuffer */
extern uint8_t rs232_input_buffer[RS232_BUFFERSIZE];
/** @brief Leseposition */
extern uint8_t rs232_input_read_pos;
/** @brief Schreibposition */
extern uint8_t rs232_input_write_pos;
/*@}*/
 
/**
 * @name Puffer f�r zu sendende Zeichen
 * In diesem Ringpuffer werden zu sendende Zeichen abgelegt.
 */
/*@{*/
/** @brief Sende-Ringbuffer */
extern uint8_t rs232_output_buffer[RS232_BUFFERSIZE];
/** @brief Leseposition */
extern uint8_t rs232_output_read_pos;
/** @brief Schreibposition */
extern uint8_t rs232_output_write_pos;
/*@}*/
 
#endif
