/*
 *    Utilities
 *    Copyright (C) 2011  Hochschule Bremen
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


/** @brief: Utilities
*/
     
#include "c515c.h"
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
