 /**
 * @file util.h
 * @brief Utilities
 *
 * Utility functions
 */

#ifndef _UTIL_H_
#define _UTIL_H_

#include "types.h"

/*
 * @brief Wartet bis die Übergeben Condition den Wert true hat
 */
#ifndef TARGET_HOST
	#define WAIT_FOR(condition) \
		while(!condition) { }
#else
	#include "ctest.h"
#endif

/*
 * @brief Wait for n usecs
 *
 * @param	usecs	Count of usecs to wait for
 */
void udelay(uint32_t usecs);

/*
 * @brief Wait for n msecs
 *
 * @param	msecs	Count of msecs to wait for
 */
void mdelay(uint32_t msecs);
                            
/**
 * @brief Restore interrupt state
 *
 * Restore the interrupt enable state, undo last enable_interrupts() call.
 */
void restore_enable_interrupts();

/**
 * @brief Enable or disable interrupts
 *
 * @param	enable	0 = disable interrupts, 1 = enable interrupts
 */
void enable_interrupts(bool enable);

#endif

