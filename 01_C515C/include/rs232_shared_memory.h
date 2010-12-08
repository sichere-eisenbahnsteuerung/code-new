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

/// @brief Größe der Ringbuffer in Bytes
#define RS232_BUFFERSIZE 10

/**
 * @name Puffer für empfangene Zeichen
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
 * @name Puffer für zu sendende Zeichen
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