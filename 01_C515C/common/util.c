/** @brief: Utilities
*/
     
#include <REG515C.H>
#include "util.h"
uint8_t restore_EAL;

void restore_enable_interrupts()
{
    EAL = restore_EAL;
}		   

void enable_interrupts(bool enable)
{
    restore_EAL = EAL;
	EAL = enable;
}

void udelay(uint32_t usecs)
{
	/* FIXME */
}


void mdelay(uint32_t msecs)
{
	/* FIXME */
}
