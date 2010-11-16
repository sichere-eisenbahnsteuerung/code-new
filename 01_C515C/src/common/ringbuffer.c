#include "ringbuffer.h"
#include "util.h"

void ringbuffer_init(ringbuffer_t *buffer) {
	uint16_t i=0;
    buffer->read_position = 0;
	buffer->write_position = 0;
	buffer->size = 0;
    for(;i<MAX_CONTENT;i++) {
        buffer->content[i] = NULL;
    }
}

uint8_t ringbuffer_read(ringbuffer_t *buffer) {
    uint8_t value = 0;
    
    enable_interrupts(FALSE);
    	
	if(buffer->size > 0) {
        value = buffer->content[buffer->read_position];
        buffer->content[buffer->read_position] = NULL;
        buffer->size--;
        buffer->read_position++; 
        buffer->read_position%=MAX_CONTENT;
	}
     
    restore_enable_interrupts();
    return value;
}


bool ringbuffer_empty(ringbuffer_t *buffer) {
    return (buffer->size == 0);
}

bool ringbuffer_write(ringbuffer_t *buffer, uint8_t value) {
    enable_interrupts(FALSE);

    if(buffer->size < MAX_CONTENT-1) { // always leave one NULL terminating byte
        buffer->content[buffer->write_position] = value;
        buffer->size++;
        buffer->write_position++; 
        buffer->write_position%=MAX_CONTENT; 
        
        restore_enable_interrupts();
        return TRUE;
	}
    else {
        restore_enable_interrupts();
        return FALSE;
    }

}