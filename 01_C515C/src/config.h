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
