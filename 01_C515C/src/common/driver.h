#ifndef _DRIVER_H_
#define _DRIVER_H_

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

enum bus_driver_type_t
{
	BUS_DRIVER_I2C = 0,
	BUS_DRIVER_S88 = 1,
}

struct bus_driver
{
	const char		*name;

	int (*probe)	(struct device *dev);
	int (*shutdown)	(struct device *dev);
	int (*send)		(uint8 *data, uint32 len);
	int (*recv)		(uint8 *data, uint32 len);
};

int					 register_driver	(bus_driver_type_t type, struct bus_driver *driver);
int					 unregister_driver	(bus_driver_type_t type);
struct bus_driver	*require_driver		(bus_driver_type_t type);
void				 release_driver		(bus_driver_type_t type);

#endif


