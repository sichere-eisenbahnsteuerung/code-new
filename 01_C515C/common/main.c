                       
#include <intrins.h>
#include "main.h"
#include "util.h"

#include "rs232_shared_memory.h"  
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


    while(1) {
        xpressnet_work();
    }
}
