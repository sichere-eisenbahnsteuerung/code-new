/**
 * @file
 * @ingroup leitzentrale
 * @brief Rudimentäre Leitzentrale
 *
 * Diese rudimentäre Version der Leitzentrale wechselt alle 10 Sekunden zwischen
 * zwei Fahrgeschwindigkeiten (Fahrt und Abkoppeln).
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 *
 * @sa leitzentrale.c
 */

#ifndef _LEITZENTRALE_H_
#define _LEITZENTRALE_H_

/**
 * @brief Initialisierung der Leitzentrale.
 */
void leitzentrale_init ();
   
/**
 * @brief Work-Funktion der Leitzentrale
 *
 * Funktion der Leitzentrale, die in der Zeitscheibe von
 * der Betriebsmittelverwaltung aufgerufen wird.
 * Wechselt alle 10 Sekunden zwischen den Fahrstufen
 * Fahrt und Abkuppeln.
 */
void leitzentrale_work ();

#endif
