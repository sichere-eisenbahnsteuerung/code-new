#include "xpressnet.h"
#include <REG515C.H>
#include "util.h"
#include "rs232.h"


static void write_byte(uint8_t b);
static uint8_t max_bytes_to_write();
static bool bytes_to_read();
static uint8_t read_byte();


static volatile uint8_t input_byte = 0;
static bool wait_for_answer = 1;
    

void xpressnet_init ()
{    
	wait_for_answer = 0;
    rs232_init();
}

void xpressnet_work() 
{	
	uint8_t retval;
	if(!wait_for_answer) {							// Neue Befehle ausführen
	

	}
	else { 	   										// Anwort auswerten

		if(bytes_to_read() >= 3) { 					// Header ist 3 Byte lang
			if(read_byte() != 0x01) { 				// 1. Byte muss Header 0x01 sein
				// FEHLER: Falscher Header
			}
			retval = read_byte();
			if(retval ^ 0x01 != read_byte()) { 		// Checksummen-Prüfung: 3. Byte ist XOR der ersten beiden
				// FEHLER: Falsche Checksumme
			}
			switch(retval) {
				case 0x04:
					wait_for_answer = FALSE;		// Alles ok
					break;
				default:
					break;
					// Kommunikationsfehler: NOTAUS
			}
		}
	}

    rs232_work();									// RS232-Schnittstelle aufrufen
}

static void write_byte(uint8_t b) {
	rs232_output_buffer[rs232_output_write_pos] = b;
    rs232_output_write_pos = (rs232_output_write_pos + 1) % RS232_BUFFERSIZE;
}

static uint8_t max_bytes_to_write() {
	return (rs232_output_read_pos + RS232_BUFFERSIZE - rs232_output_write_pos - 1) % RS232_BUFFERSIZE;
}

static bool bytes_to_read() {
	return rs232_input_read_pos != rs232_input_write_pos;
}	

static uint8_t read_byte() {
	uint8_t inp;
    inp = rs232_input_buffer[rs232_input_read_pos];
    rs232_input_read_pos = (rs232_input_read_pos + 1) % RS232_BUFFERSIZE;
	return inp;
}