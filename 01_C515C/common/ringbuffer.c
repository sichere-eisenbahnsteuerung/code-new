#include <REG515C.H>
#include "ringbuffer.h"

void ringbuffer_init(ringbuffer_t *buffer) 
{
	buffer->read_position = 0;
	buffer->write_position = 0;
	buffer->size = 0;
}

uint8_t ringbuffer_read(ringbuffer_t *buffer) 
{
	uint8_t interrupt_state = EAL, retval;
	
	if(buffer->size > 0) 
	{
        retval = buffer->content[buffer->read_position];
        buffer->size--;
        buffer->read_position++;
	}

    EAL = interrupt_state;

    return retval;
}

void ringbuffer_write(ringbuffer_t *buffer, uint8_t value) 
{
	uint8_t interrupt_state = EAL;

	/*
	if(buffer->size > 0) 
	{
        retval = buffer->data[buffer->read_position];
        buffer->size--;
        buffer->read_position++;
	}

    EAL = interrupt_state;

    return retval;	  
	*/
}