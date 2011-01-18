/*
 *    util Header
 *    Copyright (C) 2011 Hochschule Bremen
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

