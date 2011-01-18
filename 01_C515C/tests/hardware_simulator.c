/*
 *    hardware simulator
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

#include <memory.h>

#include "../include/types.h"
#include "hardware_simulator.h"

/* All necessary registers and flags which are available on real hardware */

hw_register_t r_psw;
hw_register_t r_tcon;
hw_register_t r_ien0;
hw_register_t r_ien1;
hw_register_t r_p3;
hw_register_t r_scon;
hw_register_t r_t2con;
hw_register_t r_ircon;
hw_register_t r_p1;
hw_register_t r_p4;
hw_register_t r_adcon0;

/*
 * Hardware byte register definition
 */

/*  CPU    */
uint8_t ACC;
uint8_t B;
uint8_t DPL;
uint8_t DPH;
uint8_t DPSEL;
uint8_t PSW;
uint8_t SP;
uint8_t SYSCON;

/*  A/D Converter     */
uint8_t ADCON0;
uint8_t ADDATH;
uint8_t ADDATL;  /* in mapped SFR area */
uint8_t ADCON1;

/*  Interrupt System  */
uint8_t IEN0;
uint8_t IEN1;
uint8_t IEN2;
uint8_t IP0;
uint8_t IP1;
uint8_t IRCON;

/*  XRAM   */
uint8_t XPAGE;

/*  Ports  */
uint8_t P0;
uint8_t P1;
uint8_t P2;
uint8_t P3;
uint8_t P4;
uint8_t P5;
uint8_t DIR5;  /* in mapped SFR area */
uint8_t P6;
uint8_t P7;

/*  Serial Channel    */
uint8_t SCON;
uint8_t SBUF;
uint8_t SRELL;
uint8_t SRELH;

/*  SSC Interface     */
uint8_t SSCCON;
uint8_t STB;
uint8_t SRB;
uint8_t SCF;
uint8_t SCIEN;
uint8_t SSCMOD;

/*  Timer0 / Timer1   */
uint8_t TCON;
uint8_t TMOD;
uint8_t TL0;
uint8_t TL1;
uint8_t TH0;
uint8_t TH1;

/*  CAP/COM Unit / Timer2 */
uint8_t CCEN;
uint8_t CCL1;
uint8_t CCH1;
uint8_t CCL2;
uint8_t CCH2;
uint8_t CCL3;
uint8_t CCH3;
uint8_t T2CON;
uint8_t CRCL;
uint8_t CRCH;
uint8_t TL2;
uint8_t TH2;

/*  Watchdog */
uint8_t WDTREL;

/*  Power Save Moders */
uint8_t PCON;
uint8_t PCON1;  /* in mapped SFR area */


/*
 * @brief Reset the hardware simulator to its defaults
 */
void hardware_simulator_reset(void)
{
    /* Set all flags + registers to their default values */
    HW_REGISTER_RESET(r_psw);
    HW_REGISTER_RESET(r_tcon);
    HW_REGISTER_RESET(r_ien0);
    HW_REGISTER_RESET(r_ien1);
    HW_REGISTER_RESET(r_p3);
    HW_REGISTER_RESET(r_scon);
    HW_REGISTER_RESET(r_t2con);
    HW_REGISTER_RESET(r_ircon);
    HW_REGISTER_RESET(r_p1);
    HW_REGISTER_RESET(r_p4);

    /* FIXME We need to initialize the byte registers with default values here */
}
