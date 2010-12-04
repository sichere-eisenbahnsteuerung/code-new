#include "xpressnet.h"
#include <REG515C.H>
#include "util.h"
#include "rs232.h"
#include "xpressnet_shared_memory.h"	
#include "rs232_shared_memory.h"

/* XpressNet-Konstanten */
#define V_STOP 0x00
#define V_ABKUPPELN 0x08
#define V_ANKUPPELN 0x1F
#define V_FAHRT 0xDD
				   
/* XpressNet-Addressen */
#define XPRESSNET_LOK1 0x01
#define XPRESSNET_LOK2 0x02
#define XPRESSNET_WEICHE1 0x03
#define XPRESSNET_WEICHE2 0x04
#define XPRESSNET_WEICHE3 0x02
#define XPRESSNET_ENTKUPPLER1 0x06
#define XPRESSNET_ENTKUPPLER2 0x05



/* Funktionen zur Befehlsabarbeitung */ 
static void checkForInput();
static void checkForCommands();	
static void commandWeiche();
static void commandEntkuppler(); 
static void commandLok();	

/* Funktionen zur Konvertierung von XpressNet-Befehlen */ 
static bool writeSchaltbefehl(uint8_t address, uint8_t output, bool activate);
static bool writeFahrbefehl(uint8_t address, uint8_t speed);

/* Funktionen zum Lesen und Schreiben der RS232-Ringbuffer */
static uint8_t write_byte(uint8_t b);
static uint8_t max_bytes_to_write();
static uint8_t bytes_to_read();
static uint8_t read_byte();
static uint8_t peek_byte();

/* Lokale Variablen */
static bool wait_for_answer = TRUE;					// Warten auf Befehlsbestätigung vom LI101F	 
static bool activation_pending = FALSE;				// Der aktuelle Befehl ist der Deaktivierungsbefehl, die Aktivierung muss noch gesendet werden
    

void xpressnet_init ()
{    
	wait_for_answer = 0;
    rs232_init();
}

void xpressnet_work() 
{	
	checkForInput();								// Anworten auswerten

	if(!wait_for_answer) {							// Antwort erhalten? Neue Befehle ausführen
		checkForCommands();
	}

    rs232_work();									// RS232-Schnittstelle aufrufen
}


/* 
 * Funktionen zur Befehlsverarbeitung
 */ 
				 
static void checkForCommands() {
	if(streckenbefehl_ev_xpressnet.target != IDLE)
	{
		commandLok();
		commandWeiche();
		commandEntkuppler();
	}
}

				 
static void commandLok() {
	uint8_t xpressnet_address = 0, speed = 0;	 
	 
	// XpressNet-Adresse bestimmen
	switch(streckenbefehl_ev_xpressnet.target)
	{
		case LOK1:
			xpressnet_address = XPRESSNET_LOK1;
			break;
		case LOK2:  
			xpressnet_address = XPRESSNET_LOK2;
			break;
		default:
			// Kein Entkuppler
			return;
	}
	
	switch(streckenbefehl_ev_xpressnet.command) 
	{
		case 0x00:
			speed = V_STOP;
			break;
		case 0x01:
			speed = V_ABKUPPELN;
			break;	 
		case 0x02:
			speed = V_ANKUPPELN;
			break;
		case 0x03:
			speed = V_FAHRT;
			break;
		default:
			// Ungültiger Befehl
			return;
	}
				 
	if(writeFahrbefehl(xpressnet_address, speed))
	{
		// TODO: FEHLER;
		return;
	}
}

				 
static void commandEntkuppler() {
	uint8_t xpressnet_address = 0;

	// XpressNet-Adresse bestimmen
	switch(streckenbefehl_ev_xpressnet.target)
	{
		case ENTKUPPLER1:
			xpressnet_address = XPRESSNET_ENTKUPPLER1;
			break;
		case ENTKUPPLER2:  
			xpressnet_address = XPRESSNET_ENTKUPPLER2;
			break;
		default:
			// Kein Entkuppler
			return;
	}
	
	if(!activation_pending) {	  
		// Entkuppler erst deaktivieren
		if(!writeSchaltbefehl(xpressnet_address, 0, FALSE))
		{
			// TODO: FEHLER;
			return;
		}
		activation_pending = TRUE;
   }
   else {		  							 
		// Entkuppler aktivieren
		if(!writeSchaltbefehl(xpressnet_address, 0, TRUE))
		{
			// TODO: FEHLER;
			return;
		}
		activation_pending = FALSE;
	}
}

				 
static void commandWeiche() {
	uint8_t xpressnet_address = 0;
	
	// XpressNet-Adresse bestimmen
	switch(streckenbefehl_ev_xpressnet.target)
	{
		case WEICHE1:
			xpressnet_address = XPRESSNET_WEICHE1;
			break;
		case WEICHE2:  
			xpressnet_address = XPRESSNET_WEICHE2;
			break;
		case WEICHE3:	
			xpressnet_address = XPRESSNET_WEICHE3;
			break;
		default:
			// Keine Weiche
			return;
	}
	
	if(!activation_pending) {	  
		// Weiche erst in der anderen Richtung deaktivieren
		if(!writeSchaltbefehl(xpressnet_address, 1-streckenbefehl_ev_xpressnet.command, FALSE))
		{
			// TODO: FEHLER;
			return;
		}
		activation_pending = TRUE;
   }
   else {		  							 
		// Weiche in der gewünschten Richtung aktivieren
		if(!writeSchaltbefehl(xpressnet_address, streckenbefehl_ev_xpressnet.command, TRUE))
		{
			// TODO: FEHLER;
			return;
		}
		activation_pending = FALSE;
	}
}

static void checkForInput() 
{						 
	uint8_t retval;
	
	if(bytes_to_read() > 0)														// Wenn Eingabe vorhanden
	{
		switch(peek_byte())													// Erstes Headerbyte unterscheidet die Nachrichten
		{
			/*
			 * 0x01: Antwort auf einen Befehl
	 		 */
			case 0x01:									
				if(bytes_to_read() >= 3) { 									// Antwort ist 3 Byte lang
					read_byte();											// Headerbyte lesen
					retval = read_byte();
					if(retval ^ 0x01 != read_byte()) { 						// Checksummen-Prüfung: 3. Byte ist XOR der ersten beiden
						// TODO: FEHLER: Falsche Checksumme
					}
					switch(retval) {
						case 0x04:
							wait_for_answer = FALSE;						// Alles ok
							if(!activation_pending) {
								streckenbefehl_ev_xpressnet.target = IDLE;	// Nach erfolgter Aktivierung Streckenbefehl löschen
							}
							break;
						default:
							break;
							// TODO: Kommunikationsfehler: NOTAUS
					}
				}
				break;
			default:
				// TODO: Behandlung von anderen Nachrichten
				read_byte();
		}
	}
}

/* 
 * Funktionen zur Konvertierung von XpressNet-Befehlen (siehe auch xpressnet_li101f.pdf, 3.24 und 3.26)
 */ 

static bool writeSchaltbefehl(uint8_t address, uint8_t output, bool activate) {
	uint8_t xor_byte=0;

	if(max_bytes_to_write() < 4) 						// Vier Byte müssen für die Nachricht frei sein
	{
		return FALSE;
	}

	xor_byte ^= write_byte(0x52); 					   	// Header
	xor_byte ^= write_byte(address >> 2);	   			// Address-Gruppe (Adresse / 4), die letzten zwei Bit stehen im nächsten Byte

	if(activate) {
		xor_byte ^= write_byte(
				0x88 | 									// Aktivierungsbefehl
				(address & 0x03) << 1	|				// die beiden Address-LSB
				output);								// der Ausgang des Schaltempfängers
	}
	else {
		xor_byte ^= write_byte(
				0x80 | 									// Deaktivierungsbefehl
				(address & 0x03) << 1	|		// die beiden Address-LSB
				output);								// der Ausgang des Schaltempfängers
	}

	write_byte(xor_byte);
	
	wait_for_answer = TRUE;
	
	return TRUE;	
}

static bool writeFahrbefehl(uint8_t address, uint8_t speed) {
	uint8_t xor_byte=0;	
		
	if(max_bytes_to_write() < 6) 						// Sechs Byte müssen für die Nachricht frei sein
	{
		return FALSE;
	}

	xor_byte ^= write_byte(0xE4); 					   	// Header	
	xor_byte ^= write_byte(0x13); 					   	// Header für 128-stufige Geschwindigkeiten
	xor_byte ^= write_byte(0x00); 					   	// Adresse High (immer 0)	 
	xor_byte ^= write_byte(address); 					// Adresse Low
		 
	xor_byte ^= write_byte(speed); 						// Geschwindigkeit

	write_byte(xor_byte);
	
	wait_for_answer = TRUE;

	return TRUE;	
}


/*
 * Funktionen zum Lesen und Schreiben der RS232-Ringbuffer
 */

static uint8_t write_byte(uint8_t b) {
	rs232_output_buffer[rs232_output_write_pos] = b;
    rs232_output_write_pos = (rs232_output_write_pos + 1) % RS232_BUFFERSIZE;
	return b;
}

static uint8_t max_bytes_to_write() {
	return (rs232_output_read_pos + RS232_BUFFERSIZE - rs232_output_write_pos - 1) % RS232_BUFFERSIZE;
}

static uint8_t bytes_to_read() {
	return (rs232_input_write_pos + RS232_BUFFERSIZE - rs232_input_read_pos) % RS232_BUFFERSIZE;
}	

static uint8_t read_byte() {
	uint8_t inp;
    inp = rs232_input_buffer[rs232_input_read_pos];
    rs232_input_read_pos = (rs232_input_read_pos + 1) % RS232_BUFFERSIZE;
	return inp;
}		

static uint8_t peek_byte() {
	return rs232_input_buffer[rs232_input_read_pos];
}	
	  