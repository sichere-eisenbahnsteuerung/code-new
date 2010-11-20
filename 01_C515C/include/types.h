#ifndef _TYPES_H_
#define _TYPES_H_

/*
 * Application specific types
 */

/*
 * @brief   Describes which type of a train we have. There are two possible kinds of a
 *          type currently as we have two trains running in the rails.
 */
enum train_t
{
    TRAIN_0,
    TRAIN_1
};

enum bool_t
{
    TRUE = 1,
    FALSE = 0
};


/*
 * Common types
 */

typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned char uint8_t;
typedef signed char int8_t;
                         
typedef enum bool_t bool;



/*
 * Defines
 */

#define NULL 0

#endif

