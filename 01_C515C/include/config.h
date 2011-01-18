/*
 *    config Header
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

#ifndef _CONFIG_H_
#define _CONFIG_H_

/* 
 * Here we define several config-options for the build program. For example we want to
 * build the program with the Fahrprogramm for task one and not the one for task two 
 * than we do the following:
 *
 * #define CONFIG_FAHRPROGRAMM_1
 * #undef  CONFIG_FAHRPROGRAMM_2
 */

/*
 * Available config options:
 * - CONFIG_FAHRPROGRAMM_1
 * - CONFIG_FAHRPROGRAMM_2
 */

#define CONFIG_FAHRPROGRAMM_1
#undef  CONFIG_FAHRPROGRAMM_2

#endif
