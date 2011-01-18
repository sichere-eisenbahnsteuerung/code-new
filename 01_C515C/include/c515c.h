/*
 *    C515c Header
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

#ifndef _C515C_H_
#define _C515C_H_

/*
 * Wenn wir auf dem Entwicklungsrechner für die Unit-Tests kompilieren, dann haben wir
 * keinen Interrupt-Handler Support im C-Compiler
 */
#ifndef TARGET_HOST
#define INTERRUPT(n) interrupt n
#else
#define INTERRUPT(n)
#endif

/*
 * Wenn wir auf dem Entwicklungsrechner für die Unit-Tests kompilieren, dann
 * Timer simulieren.
 */
#ifndef TARGET_HOST
#define ZEITSCHEIBE_SCHLEIFE
#else
#include "timer_simulator.h"
#define ZEITSCHEIBE_SCHLEIFE timer1_simulate()
#endif

/*
 * In der Unit-Test Umgebung können wir nicht die Register verwenden, die der Keil
 * Compiler definiert, sondern verwenden hier unsere eigenen.
 */
#ifndef TARGET_HOST
#include <REG515C.h>
#else
#include <hardware_simulator.h>
#endif

/**
 * @brief Quarztakt: 10Mhz
 */
#define QUARZTAKT 10000000L	 
/**
 * @brief Maschinenzyklus (Machine/Instruction cycle): Quarztakt / 6.
 */
#define MACHINE_CYCLE QUARZTAKT / 6

#endif
