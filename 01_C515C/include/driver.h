#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "types.h"
#include "error.h"

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define MAX_DRIVERS		10

typedef enum bus_driver_type
{
	BUS_DRIVER_I2C = 0,
	BUS_DRIVER_S88 = 1
} bus_driver_type_t;

typedef struct bus_driver
{
	const char		*name;

	int (*probe)	(struct device *);
	int (*shutdown)	(struct device *);
	int (*send)		(uint8_t, uint32_t );
	int (*recv)		(uint8_t, uint32_t );
} bus_driver_t;

int					 register_driver	(bus_driver_type_t, bus_driver_t *);
int					 unregister_driver	(bus_driver_type_t);
struct bus_driver	*require_driver		(bus_driver_type_t);
void				 release_driver		(bus_driver_type_t);

#endif


