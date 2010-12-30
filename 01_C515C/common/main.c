                       
#include "main.h"
#include "betriebsmittelverwaltung.h"


/*
 * @brief The method which gets called initialy by the processor
 */
void main()
{
	betriebsmittelverwaltung_init();
	
	betriebsmittelverwaltung_work();
}
