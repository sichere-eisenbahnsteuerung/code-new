/*
 *    structs Header
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

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

/*
 * @brief   FIXME
 */
struct sensor_data
{
    uint8_t content[2];
    uint8_t error;
};

/*
 * @brief   FIXME
 */
struct track_segment
{
    uint8_t nr;
    uint8_t next1;
    uint8_t prev1;
    uint8_t next2;
    uint8_t prev2;
    uint8_t next_switch;
    uint8_t prev_switch;
    uint8_t next_sensor;
    uint8_t prev_sensor;
};

#endif

