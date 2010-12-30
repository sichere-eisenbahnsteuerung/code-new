/**
 * @file
 * @ingroup includes
 * @brief C515C-Systemregister
 *
 * Verwaltung der C515C-Systemregister und der Simulation f�r
 * Tests am PC.
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
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
