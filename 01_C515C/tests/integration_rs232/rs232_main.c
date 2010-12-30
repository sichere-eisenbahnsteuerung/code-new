
#include "main.h"
#include "util.h"

#include "xpressnet.h"	 
#include "rs232.h"
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
 * @brief The method which gets called initially by the processor
 * 
 * Hauptfunktion für den Integrationstest RS232.
 */
void main()
{
    uint8_t inp=0;

	init_common();

    while(1) {
        xpressnet_work();	 
    	rs232_work();
		if(streckenbefehl_xpressnet.target == IDLE) {
			if(inp == 0) {
				inp++;
				streckenbefehl_xpressnet.target = ENTKUPPLER_E1;
				streckenbefehl_xpressnet.command = 0;
			}		
			else if(inp == 1) {
				inp++;
				streckenbefehl_xpressnet.target = ENTKUPPLER_E1;
				streckenbefehl_xpressnet.command = 0;
			}
			else if(inp == 2) {
				inp++;	  
				streckenbefehl_xpressnet.target = WEICHE_A;
				streckenbefehl_xpressnet.command = 0;
			}
			else if(inp == 3) {
				inp++;	  		 
				streckenbefehl_xpressnet.target = WEICHE_B;
				streckenbefehl_xpressnet.command = 0;
			}	
			else if(inp == 4) {
				inp++;	  		 
				streckenbefehl_xpressnet.target = WEICHE_C;
				streckenbefehl_xpressnet.command = 1;
			}
            else {
                break;
            }
		}
        
    }

        
    CloseComport(0);
}
