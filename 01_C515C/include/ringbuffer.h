#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_


#include "types.h"

#define RINGBUFFER_SIZE 50

typedef struct ringbuffer {
	uint8_t content[RINGBUFFER_SIZE];
	uint8_t read_position;
	uint8_t write_position;
	uint8_t size;
} ringbuffer_t;

#endif