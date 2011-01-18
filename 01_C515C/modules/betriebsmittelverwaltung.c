/*
 *    Die Betriebsmittelverwaltung ist für die Verwaltung von Ressourcen wie Speicherplatz und Rechenzeit verantwortlich.
 *    Copyright (C) 2011 Hanno Fellmann
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
 */
 

#include "betriebsmittelverwaltung.h"  
#include "leitzentrale.h"
#include "rs232_shared_memory.h"   
#include "xpressnet_shared_memory.h"
#include "c515c.h"	 
#include "util.h"
#include "xpressnet.h"
#include "rs232.h"


/*
 * Shared Memory RS232 
 */

uint8_t rs232_input_buffer[RS232_BUFFERSIZE] = {0};  
uint8_t rs232_input_read_pos = 0;          
uint8_t rs232_input_write_pos = 0;            

uint8_t rs232_output_buffer[RS232_BUFFERSIZE] = {0};
uint8_t rs232_output_read_pos = 0;          
uint8_t rs232_output_write_pos = 0;


/*
 * Shared Memory Streckenbefehle 
 */

streckenbefehl streckenbefehl_xpressnet = { IDLE, 0x00 };

/**
 * @brief Timer 1 Steps für 10ms  (1/100 sek)
 *
 * Berechnung: MACHINE_CYCLE x (1/100).
 *
 * Genauigkeitsfehler des Timers: ca. -0.01%
 */
#define TIMER1_STEPS MACHINE_CYCLE / 100
							  
/**
 * @brief Timer 1 Overflows bis 10ms.
 */
#define TIMER1_OVERFLOWS 101

/**
 * @brief Timer 1 Reload Werte
 *
 * Berechnung: 256 - MACHINE_CYCLE x (1/100).
 */
#define TIMER1_RELOAD 0x100L - TIMER1_STEPS / TIMER1_OVERFLOWS



/**
 * @brief Initialisiert Timer 1.
 *
 * Timer 1 wird für die Verwendung für die Module konfiguriert.
 */
void timer1_init ();

/**
 * @brief Interner Zähler für Timer 1.
 *
 * Zählt die Overflows von Timer 1, bis 10ms verstrichen sind.
 */
static uint16_t overflow_count = 0;	

uint16_t timer_value[1] = {0};
	
void betriebsmittelverwaltung_init() 
{
	rs232_init();
    xpressnet_init(); 
	leitzentrale_init();
	timer1_init();		
    enable_interrupts(TRUE);
}

void betriebsmittelverwaltung_work() {
	while(1) {
		leitzentrale_work();
		xpressnet_work();
		rs232_work();
        ZEITSCHEIBE_SCHLEIFE;
	}
}
  

void timer1_init ()
{
	// Timer 1 konfigurieren (Timer 0 nicht verändern)
	// Mode 2 -> 8-Bit Auto-Reload
    TMOD = (TMOD & 0x0F) | 0x20;  /* Set Mode 0 */
		   
    TH1 = TIMER1_RELOAD;
    TL1 = TH1;
    ET1 = 1;                      /* Enable Timer 1 Interrupts */
    TR1 = 1;                      /* Start Timer 1 Running */
}	

/**
 * @name Interrupt-Routinen
 */
/*@{*/
/**
/**
 * @brief Interrupt-Routine für Timer 1.
 *
 * Inkrementiert die Timerwerte alle 10ms.
 */
void timer1_interrupt () INTERRUPT(3)
{
    overflow_count++;   /* Increment the overflow count */
    if(overflow_count >= TIMER1_OVERFLOWS) {
        overflow_count = 0;
        timer_value[TIMER_LEITZENTRALE]++;
    }
}		 
/*@}*/
