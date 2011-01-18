/*
 *    pins Header
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

#ifndef _PINS_H_
#define _PINS_H_

/* Pin configuration */
sbit PIN_EMERGENCY_STOP     = P3^4;
sbit PIN_RS232_CTS          = P3^5;
sbit PIN_S88_PS             = P5^0;
sbit PIN_S88_RESET          = P5^1;
sbit PIN_S88_CLK            = P5^2;
sbit PIN_S88_DATA           = P5^3;
sbit PIN_AS_PORT_I2C_SDA    = P5^4;
sbit PIN_AS_PORT_I2C_SCL    = P5^5;
sbit PIN_RESET              = P1^0;

#endif

