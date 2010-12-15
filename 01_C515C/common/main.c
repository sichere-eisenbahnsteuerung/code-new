                    
#include "main.h"
#include "util.h"   
#include "c515c.h"

#include "xpressnet.h"	 
#include "rs232.h"
#include "stdio.h"
#include "rs232_win_linux.h"
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

	streckenbefehl_ev_xpressnet.target = LOK_2;
	streckenbefehl_ev_xpressnet.command = 3;
    
    while(1) {
        xpressnet_work();	 
    	rs232_work();
		if(streckenbefehl_ev_xpressnet.target == IDLE) {
			if(inp == 0) {
				inp++;	  
				streckenbefehl_ev_xpressnet.target = ENTKUPPLER_E1;
				streckenbefehl_ev_xpressnet.command = 1;
			}		
			else if(inp == 1) {
				inp++;	  		 
				streckenbefehl_ev_xpressnet.target = WEICHE_A;
				streckenbefehl_ev_xpressnet.command = 0;
			}
            else {
                break;
            }
		}

    }
    CloseComport(0);
}
