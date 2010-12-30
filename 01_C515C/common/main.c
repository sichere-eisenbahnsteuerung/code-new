                       
#include <intrins.h>
#include "main.h"
#include "util.h"

#include "xpressnet.h"	 
#include "rs232.h"

/*
 * @brief Initialize common stuff for the main program
 */
void init_common(void)
{
	enable_interrupts(1);		 
    rs232_init();
    xpressnet_init();
}

/*
 * @brief The method which gets called initialy by the processor
 */
void main()
{
    uint8_t inp=0;

	init_common();

	// TODO: Betriebsmittelverwaltung aufrufen
}
