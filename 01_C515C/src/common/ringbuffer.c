#include "ringbuffer.h"

void ringbuffer_init(RINGBUFFER_T *buffer) {
	buffer->read_position = 0;
	buffer->write_position = 0;
	buffer->size = 0;
}

uint8_t ringbuffer_read(RINGBUFFER_T *buffer) {
	uint8_t interrupt_state = IE, retval;

	if(buffer->size > 0) {
        retval = buffer->data[buffer->read_position];
        buffer->size--;
        buffer->read_position++;
	}

    IE = interrupt_state;

    return retval;
}

uint8_t ringbuffer_write(RINGBUFFER_T *buffer) {
	uint8_t interrupt_state = IE;

	if(buffer->size > 0) {
        retval = buffer->data[buffer->read_position];
        buffer->size--;
        buffer->read_position++;
	}

    IE = interrupt_state;

    return retval;
}