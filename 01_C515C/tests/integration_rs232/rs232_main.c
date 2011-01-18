/*
 *    Initialize common stuff for the main program
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

#include "main.h"
#include "util.h"

#include "betriebsmittelverwaltung.h"	 
#include "rs232.h"
#include "rs232_win_linux.h"

/*
 * @brief The method which gets called initially by the processor
 * 
 * Hauptfunktion f�r den Integrationstest RS232.
 */
void main()
{
    betriebsmittelverwaltung_init();
    betriebsmittelverwaltung_work();
        
    CloseComport(0);
}
