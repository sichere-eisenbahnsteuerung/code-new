#ifndef _HARDWARE_SIMULATOR_H_
#define _HARDWARE_SIMULATOR_H_

/* 
 * Redefine some macros 
 */

/* 
 * Hardware bit-register definition
 */
typedef struct
{
    uint8_t b0:1;
    uint8_t b1:1;
    uint8_t b2:1;
    uint8_t b3:1;
    uint8_t b4:1;
    uint8_t b5:1;
    uint8_t b6:1;
    uint8_t b7:1;
} __attribute__((packed)) hw_register_t;

#define HW_REGISTER_BIT(r,n) ((*(volatile struct hw_register_t*)&r)->b##n)
#define HW_REGISTER_RESET(r) memset(&r, 0, sizeof(hw_register_t))

/* 
 * All hardware registers we have on the C515C microcontroller 
 */
extern hw_register_t r_psw;
extern hw_register_t r_tcon;
extern hw_register_t r_ien0;
extern hw_register_t r_ien1;
extern hw_register_t r_p3;
extern hw_register_t r_scon;
extern hw_register_t r_t2con;
extern hw_register_t r_adcon0;
extern hw_register_t r_ircon;
extern hw_register_t r_p1;
extern hw_register_t r_p4;

/* PSW */
#define CY  HW_REGISTER_BIT(r_psw, 7)
#define AC  HW_REGISTER_BIT(r_psw, 6)
#define F0  HW_REGISTER_BIT(r_psw, 5)
#define RS1 HW_REGISTER_BIT(r_psw, 4)
#define RS0 HW_REGISTER_BIT(r_psw, 3)
#define OV  HW_REGISTER_BIT(r_psw, 2)
#define F1  HW_REGISTER_BIT(r_psw, 1)
#define P   HW_REGISTER_BIT(r_psw, 9)

/* TCON */
#define TF1 HW_REGISTER_BIT(r_tcon, 7)
#define TR1 HW_REGISTER_BIT(r_tcon, 6)
#define TF0 HW_REGISTER_BIT(r_tcon, 5)
#define TR0 HW_REGISTER_BIT(r_tcon, 4)
#define IE1 HW_REGISTER_BIT(r_tcon, 3)
#define IT1 HW_REGISTER_BIT(r_tcon, 2)
#define IE0 HW_REGISTER_BIT(r_tcon, 1)
#define IT0 HW_REGISTER_BIT(r_tcon, 0)

/* IEN0 */
#define EAL HW_REGISTER_BIT(r_ien0, 7)
#define WDT HW_REGISTER_BIT(r_ien0, 6)
#define ET2 HW_REGISTER_BIT(r_ien0, 5)
#define ES  HW_REGISTER_BIT(r_ien0, 4)
#define ET1 HW_REGISTER_BIT(r_ien0, 3)
#define EX1 HW_REGISTER_BIT(r_ien0, 2)
#define ET0 HW_REGISTER_BIT(r_ien0, 1)
#define EX0 HW_REGISTER_BIT(r_ien0, 0)

/* IEN1 */
#define EXEN2 HW_REGISTER_BIT(r_ien1, 7)
#define SWDT HW_REGISTER_BIT(r_ien1, 6)
#define EX6 HW_REGISTER_BIT(r_ien1, 5)
#define EX5 HW_REGISTER_BIT(r_ien1, 4)
#define EX4 HW_REGISTER_BIT(r_ien1, 3)
#define EX3 HW_REGISTER_BIT(r_ien1, 2)
#define EX2 HW_REGISTER_BIT(r_ien1, 1)
#define EADC HW_REGISTER_BIT(r_ien1, 0)

/* P3 */
#define RD  HW_REGISTER_BIT(r_p3, 7)
#define WR  HW_REGISTER_BIT(r_p3, 6)
#define T1  HW_REGISTER_BIT(r_p3, 5)
#define T0  HW_REGISTER_BIT(r_p3, 4)
#define INT1 HW_REGISTER_BIT(r_p3, 3)
#define INT0 HW_REGISTER_BIT(r_p3, 2)
#define TXD HW_REGISTER_BIT(r_p3, 1)
#define RXD HW_REGISTER_BIT(r_p3, 0)

/* SCON */
#define SM0 HW_REGISTER_BIT(r_scon, 7)
#define SM1 HW_REGISTER_BIT(r_scon, 6)
#define SM2 HW_REGISTER_BIT(r_scon, 5)
#define REN HW_REGISTER_BIT(r_scon, 4)
#define TB8 HW_REGISTER_BIT(r_scon, 3)
#define RB8 HW_REGISTER_BIT(r_scon, 2)
#define TI  HW_REGISTER_BIT(r_scon, 1)
#define RI  HW_REGISTER_BIT(r_scon, 0)

/* T2CON */
#define T2PS HW_REGISTER_BIT(r_t2con, 7)
#define I3FR HW_REGISTER_BIT(r_t2con, 6)
#define I2FR HW_REGISTER_BIT(r_t2con, 5)
#define T2R1 HW_REGISTER_BIT(r_t2con, 4)
#define T2RO HW_REGISTER_BIT(r_t2con, 3)
#define T2CM HW_REGISTER_BIT(r_t2con, 2)
#define T2I1 HW_REGISTER_BIT(r_t2con, 1)
#define T2I0 HW_REGISTER_BIT(r_t2con, 0)

/* ADCON0 */
#define BD  HW_REGISTER_BIT(r_adcon0, 7)
#define CLK HW_REGISTER_BIT(r_adcon0, 6)
#define ADEX HW_REGISTER_BIT(r_adcon0, 5)
#define BSY HW_REGISTER_BIT(r_adcon0, 4)
#define ADM HW_REGISTER_BIT(r_adcon0, 3)
#define MX2 HW_REGISTER_BIT(r_adcon0, 2)
#define MX1 HW_REGISTER_BIT(r_adcon0, 1)
#define MX0 HW_REGISTER_BIT(r_adcon0, 0)

/* IRCON */
#define T2  HW_REGISTER_BIT(r_ircon, 7)
#define CLKOUT HW_REGISTER_BIT(r_ircon, 6)
#define T2EX HW_REGISTER_BIT(r_ircon, 5)
#define INT2 HW_REGISTER_BIT(r_ircon, 4)
#define INT6 HW_REGISTER_BIT(r_ircon, 3)
#define INT5 HW_REGISTER_BIT(r_ircon, 2)
#define INT4 HW_REGISTER_BIT(r_ircon, 1)
#define INT3 HW_REGISTER_BIT(r_ircon, 0)

/* P1 */
#if 0
#define T2  HW_REGISTER_BIT(r_p1, 7)
#define CLKOUT HW_REGISTER_BIT(r_p1, 6)
#define T2EX HW_REGISTER_BIT(r_p1, 5)
#define INT2 HW_REGISTER_BIT(r_p1, 4)
#define INT6 HW_REGISTER_BIT(r_p1, 3)
#define INT5 HW_REGISTER_BIT(r_p1, 2)
#define INT4 HW_REGISTER_BIT(r_p1, 1)
#define INT3 HW_REGISTER_BIT(r_p1, 0)
#endif

/* P4 */
#define RXDC HW_REGISTER_BIT(r_p4, 7)
#define TXDC HW_REGISTER_BIT(r_p4, 6)
#define INT8 HW_REGISTER_BIT(r_p4, 5)
#define SLS HW_REGISTER_BIT(r_p4, 4)
#define STO HW_REGISTER_BIT(r_p4, 3)
#define SRI HW_REGISTER_BIT(r_p4, 2)
#define SCLK HW_REGISTER_BIT(r_p4, 1)
#define ADST HW_REGISTER_BIT(r_p4, 0)

/*
 * Hardware byte register definition
 */

/*  CPU    */
extern uint8_t ACC;
extern uint8_t B;
extern uint8_t DPL;
extern uint8_t DPH;
extern uint8_t DPSEL;
extern uint8_t PSW;
extern uint8_t SP;
extern uint8_t SYSCON;

/*  A/D Converter     */
extern uint8_t ADCON0;
extern uint8_t ADDATH;
extern uint8_t ADDATL;  /* in mapped SFR area */
extern uint8_t ADCON1;

/*  Interrupt System  */
extern uint8_t IEN0;
extern uint8_t IEN1;
extern uint8_t IEN2;
extern uint8_t IP0;
extern uint8_t IP1;
extern uint8_t IRCON;

/*  XRAM   */
extern uint8_t XPAGE;

/*  Ports  */
extern uint8_t P0;
extern uint8_t P1;
extern uint8_t P2;
extern uint8_t P3;
extern uint8_t P4;
extern uint8_t P5;
extern uint8_t DIR5;  /* in mapped SFR area */
extern uint8_t P6;
extern uint8_t P7;

/*  Serial Channel    */
extern uint8_t SCON;
extern uint8_t SBUF;
extern uint8_t SRELL;
extern uint8_t SRELH;

/*  SSC Interface     */
extern uint8_t SSCCON;
extern uint8_t STB;
extern uint8_t SRB;
extern uint8_t SCF;
extern uint8_t SCIEN;
extern uint8_t SSCMOD;

/*  Timer0 / Timer1   */
extern uint8_t TCON;
extern uint8_t TMOD;
extern uint8_t TL0;
extern uint8_t TL1;
extern uint8_t TH0;
extern uint8_t TH1;

/*  CAP/COM Unit / Timer2 */
extern uint8_t CCEN;
extern uint8_t CCL1;
extern uint8_t CCH1;
extern uint8_t CCL2;
extern uint8_t CCH2;
extern uint8_t CCL3;
extern uint8_t CCH3;
extern uint8_t T2CON;
extern uint8_t CRCL;
extern uint8_t CRCH;
extern uint8_t TL2;
extern uint8_t TH2;

/*  Watchdog */
extern uint8_t WDTREL;

/*  Power Save Moders */
extern uint8_t PCON;
extern uint8_t PCON1;  /* in mapped SFR area */

/*
 * Methods
 */

void hardware_simulator_reset(void);

#endif

