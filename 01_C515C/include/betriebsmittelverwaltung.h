/**
 * @file
 * @ingroup sharedmemory
 * @ingroup betriebsmittelverwaltung
 * @brief Rudimentäre Betriebsmittelverwaltung
 *
 * Die Betriebsmittelverwaltung ist für die Verwaltung von Ressourcen
 * wie Speicherplatz und Rechenzeit verantwortlich. Sie ruft die einzelnen 
 * Module in der Reihenfolge der Zeitscheibe auf und legt das Shared Memory an.
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 *
 * @sa betriebsmittelverwaltung.c
 */

#ifndef _BETRIEBSMITTELVERWALTUNG_H_
#define _BETRIEBSMITTELVERWALTUNG_H_

#include "types.h"

/**
 * @brief Timer für die Leitzentrale.
 */
#define TIMER_LEITZENTRALE 0


/**
 * @brief Timer-Werte für die Module.
 *
 * Timer zur Benutzung durch die Module. Die Werte werden alle 10ms
 * inkrementiert.
 */
extern uint16_t timer_value[1];

/**
 * @brief Init-Funktion der Betriebsmittelverwaltung.
 *
 * Initialisiert die einzelnen Module.
 */
void betriebsmittelverwaltung_init();	

/**
 * @brief Work-Funktion der Betriebsmittelverwaltung.
 *
 * Ruft die einzelnen Module in der Zeitscheibe auf.
 */
void betriebsmittelverwaltung_work();

#endif
