#include "util.h"

/*
 * @brief Enable or disable interrupts
 *
 * @param	enable	0 = disable interrupts, 1 = enable interrupts
 */
void enable_interrupts(bool enable)
{
	IE = enable;
}

/*
 * @brief Wait for n usecs
 *
 * @param	usecs	Count of usecs to wait for
 */
void udelay(uint32_t usecs)
{
	/* FIXME */
}

/*
 * @brief Wait for n msecs
 *
 * @param	msecs	Count of msecs to wait for
 */
void mdelay(uint32_t msecs)
{
	/* FIXME */
}
