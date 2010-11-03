#include "types.h"

#define RINGBUFFER_SIZE 50

struct RINGBUFFER_T {
	uint8_t data[RINGBUFFER_SIZE];
	uint8_t read_position;
	uint8_t write_position
	uint8_t size;
}