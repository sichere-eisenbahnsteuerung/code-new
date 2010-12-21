/** 
 * @file types.h
 * @brief Global Type Definitions
 */

#ifndef TYPES_H_	// _TYPES_H_ ist durch stdlib vergeben!
#define TYPES_H_


/** @brief Boolean Type */
enum bool_t
{
    TRUE = 1,
    FALSE = 0
};



/*
 * Common types
 */

/*
 * NOTE: We can only define our own types when don't have any std lib types. Otherwise we
 * have to change our naming conventions for the types below.
 */

#ifndef _STDLIB_H_
/** @brief 32 bit unsigned integer */
typedef unsigned long uint32_t;
/** @brief 32 bit signed integer */
typedef signed long int32_t; 
/** @brief 16 bit unsigned integer */
typedef unsigned int uint16_t;
/** @brief 16 bit signed integer */
typedef signed int int16_t;
/** @brief 8 bit unsigned integer */
typedef unsigned char uint8_t;
/** @brief 8 bit signed integer */
typedef signed char int8_t;

#endif

/** @brief Boolean type */
typedef enum bool_t bool;


/*
 * Defines
 */

/** @brief NULL = 0 */
#ifndef NULL
#define NULL 0
#endif



/*
 * Application specific types
 */

/**
 * @brief   Ziel eines Streckenbefehls (entweder Lok, Weiche oder Entkoppler)
 */
typedef enum
{
	IDLE, 									/**< Kein Befehl auszufuehren */
    LOK_RED,									/**< Lok 1 */
    LOK_BLACK,									/**< Lok 2 */
	WEICHE_A,								/**< Weiche 1 */  
	WEICHE_B,								/**< Weiche 2 */
	WEICHE_C,								/**< Weiche 3 */
	ENTKUPPLER_E1,							/**< Entkuppler 1 */	
	ENTKUPPLER_E2							/**< Entkuppler 2 */
} streckenbefehl_ziel;			  

/**
 * @brief   Ein Streckenbefehl
 */
typedef struct
{
    streckenbefehl_ziel target;				/**< Ziel des Streckenbefehls */ 
	uint8_t command; 						/**< Der auszufuehrende Befehl.
											  * 
											  *	Bei einem Lokbefehl - Geschwindigkeit: 
											  *		- 0x00: Stop
											  *		- 0x01: Abkuppeln
											  *		- 0x02: Ankuppeln
											  *		- 0x03: Fahrt
											  *
											  * Bei einer Weiche:
											  *		- 0x00: Geradeaus
											  *		- 0x01: Abbiegen
											  *
											  * Bei einem Entkuppler:
											  *		- 0x00: Keine Aktion
											  *		- 0x01: Entkuppeln
											  */ 
} streckenbefehl;


#endif

