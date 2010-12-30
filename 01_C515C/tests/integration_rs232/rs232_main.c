
#include "main.h"
#include "util.h"

#include "betriebsmittelverwaltung.h"	 
#include "rs232.h"
#include "rs232_win_linux.h"

/*
 * @brief The method which gets called initially by the processor
 * 
 * Hauptfunktion für den Integrationstest RS232.
 */
void main()
{
    betriebsmittelverwaltung_init();
    betriebsmittelverwaltung_work();
        
    CloseComport(0);
}
