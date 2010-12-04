                       
#include <intrins.h>
#include "main.h"
#include "util.h"

#include "xpressnet_shared_memory.h"  
#include "rs232.h"

/*
 * @brief Initialize common stuff for the main program
 */
void init_common(void)
{
	enable_interrupts(1);
    xpressnet_init();
}

/*
 * @brief The method which gets called initialy by the processor
 */
void main()
{
    uint8_t inp=0;

	init_common();

	streckenbefehl_ev_xpressnet.target = LOK2;
	streckenbefehl_ev_xpressnet.command = 3;

    while(1) {
        xpressnet_work();
		if(streckenbefehl_ev_xpressnet.target == IDLE) {
			if(inp == 0) {
				inp++;	  
				streckenbefehl_ev_xpressnet.target = ENTKUPPLER1;
				streckenbefehl_ev_xpressnet.command = 1;
			}		
			else if(inp == 1) {
				inp++;	  		 
				streckenbefehl_ev_xpressnet.target = WEICHE1;
				streckenbefehl_ev_xpressnet.command = 0;
			}
		}

    }
}
