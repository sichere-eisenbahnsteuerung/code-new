/**
 * @file
 * @ingroup leitzentrale
 * @brief Rudiment�re Leitzentrale
 *
 * Diese rudiment�re Version der Leitzentrale wechselt alle 10 Sekunden zwischen
 * zwei Fahrgeschwindigkeiten (Fahrt und Abkoppeln).
 *
 * @author Hanno Fellmann
 * @date 08.12.2010
 */
 

#include "leitzentrale.h"
#include "betriebsmittelverwaltung.h"
#include "xpressnet_shared_memory.h"

/** 
 * @brief Die erste Fahrstufe, die angesteuert wird (Abkuppeln).
 */
#define FAHRSTUFE_1 0x01 // Abkuppeln
/** 
 * @brief Die zweite Fahrstufe, die angesteuert wird (Fahrt).
 */
#define FAHRSTUFE_2 0x03 // Fahrt

/**
 * @brief Die aktuell ausgew�hlte Fahrstufe.
 */
static uint8_t aktuelle_fahrstufe;

// Lokale Funktionsprototypen
static void send_fahrbefehl();
static bool fahrbefehl_idle();

void leitzentrale_init() {
	// Zu Beginn: Fahrstufe 0 (Stop)
	aktuelle_fahrstufe = 0x00;
}

void leitzentrale_work() {	  	
	// Alle 10 Sekunden -> 1000 x 10ms
	if(timer_value[0] >= 1000 && fahrbefehl_idle()) {
		// Timer zur�cksetzen
		timer_value[0] = 0;
		// Fahrstufe wechseln
		if(aktuelle_fahrstufe == FAHRSTUFE_1) {
			aktuelle_fahrstufe = FAHRSTUFE_2;
		}
		else {
			aktuelle_fahrstufe = FAHRSTUFE_1;
		}
		// Fahrbefehl senden
		send_fahrbefehl();
	}
}

/**
 * @brief Pr�ft, ob der letzte Streckenbefehl gesendet wurde.
 *
 * @return TRUE, wenn aktuell kein Streckenbefehl mehr 
 *         im Shared Memory zu senden ist.
 */
static bool fahrbefehl_idle() {
	return streckenbefehl_xpressnet.target == IDLE;
}

/**
 * @brief Schreibt den aktuellen Fahrbefehl ins Shared Memory,
 *        so dass er �ber XpressNet versendet wird.
 *
 * Es wird die Geschwindigkeit f�r die schwarze Lok gesetzt.
 */
static void send_fahrbefehl() {
	streckenbefehl_xpressnet.target = LOK_BLACK;
	streckenbefehl_xpressnet.command = aktuelle_fahrstufe;
}
	