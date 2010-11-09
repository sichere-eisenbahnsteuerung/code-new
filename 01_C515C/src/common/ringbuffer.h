 /**
 * @file ringbuffer.h
 * @brief Ringbuffer
 *
 * Ringbuffer structure and access functions
 */
 
#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H_


#include "types.h"

/** @brief Ringbuffer size */
#define MAX_CONTENT 50

/**
* @brief Ringbuffer data structure
*/               
typedef struct ringbuffer {
	uint8_t content[MAX_CONTENT];
	uint8_t read_position;
	uint8_t write_position;
	uint8_t size;
} ringbuffer_t;
  
/** @brief Init ringbuffer

Initialize a ringbuffer structure.

@param buffer The ringbuffer
*/
void ringbuffer_init(ringbuffer_t *buffer);


/** @brief Read byte

Reads one byte from a ringbuffer.

@param buffer The ringbuffer
@param value The value read

@return TRUE if success, FALSE if not (ringbuffer is empty)
*/
bool ringbuffer_read(ringbuffer_t *buffer, uint8_t *value);



/** @brief Write byte

Writes one byte to a ringbuffer.

@param buffer The ringbuffer
@param value The value to write

@return TRUE if success, FALSE if not (ringbuffer is full)
*/
bool ringbuffer_write(ringbuffer_t *buffer, uint8_t value);


#endif