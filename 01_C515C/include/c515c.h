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
 * In der Unit-Test Umgebung können wir nicht die Register verwenden, die der Keil
 * Compiler definiert, sondern verwenden hier unsere eigenen.
 */
#ifndef TARGET_HOST
#include <REG515C.h>
#else
#include <hardware_simulator.h>
#endif

#endif
