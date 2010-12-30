/**
 * @file
 * @ingroup sharedmemory
 * @ingroup modules
 * @brief Die Betriebsmittelverwaltung
 *
 * Die Betriebsmittelverwaltung ist f�r die Verwaltung von Ressourcen wie Speicherplatz und Rechenzeit verantwortlich. Sie ruft die einzelnen Module in der Reihenfolge der Zeitscheibe auf und legt das Shared Memory an.
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 */
 
#include "types.h"
#include "rs232_shared_memory.h"   
#include "xpressnet_shared_memory.h"


/*
 * Shared Memory RS232 
 */

uint8_t rs232_input_buffer[RS232_BUFFERSIZE] = {0};  
uint8_t rs232_input_read_pos = 0;          
uint8_t rs232_input_write_pos = 0;            

uint8_t rs232_output_buffer[RS232_BUFFERSIZE] = {0};
uint8_t rs232_output_read_pos = 0;          
uint8_t rs232_output_write_pos = 0;


/*
 * Shared Memory Streckenbefehle 
 */

streckenbefehl streckenbefehl_xpressnet = { IDLE, 0x00 };