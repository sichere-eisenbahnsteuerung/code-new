/** 
 * @file types.h
 * @brief Global Type Definitions
 */

#ifndef _TYPES_H_
#define _TYPES_H_

/*
 * Application specific types
 */

/**
 * @brief   Describes which type of a train we have. There are two possible kinds of a
 *          type currently as we have two trains running in the rails.
 */
enum train_t
{
    TRAIN_0,
    TRAIN_1
};

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

#ifndef _STDLIB_H

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

#endif

