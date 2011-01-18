/*
 *    rs232_win_linux Header
 *    Copyright (C) 2011 Teunis van Beelen(teuniz@gmail.com)
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

#ifndef rs232_INCLUDED
#define rs232_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif





int OpenComport(int, char *, int);
int PollComport(int, unsigned char *, int);
int SendByte(int, unsigned char);
int SendBuf(int, unsigned char *, int);
void CloseComport(int);
void cprintf(int, const char *);
int IsCTSEnabled(int);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif


