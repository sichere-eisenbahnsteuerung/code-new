
#include "driver.h"

struct driver_registration 
{
	struct bus_driver	*driver;
	unsigned int		 ref_count;
};

struct driver_registration drivers[MAX_DRIVERS];

/*int _register_driver(bus_driver_t *driver)   TODO: ????? zwei Funktionen register_driver?
{
	int rc = 0;

	if (driver != NULL && driver->probe != NULL)
	{
		rc = driver->probe();
	}

	return rc;
}  */

int _unregister_driver(bus_driver_t *driver)
{
	int rc = 0;

	if (driver != NULL && driver->shutdown != NULL)
	{
		rc = driver->shutdown();
	}

	return rc;
}

int check_for_driver(bus_driver_type_t type)
{
	return drivers[type].driver != NULL;
}

int register_driver(bus_driver_type_t type, bus_driver_t *driver)
{
	int rc = 0;

	/* Do we already have this driver? */
	if (!check_for_driver(type))
	{
		drivers[type].driver = driver;
		drivers[type].ref_count = 0;
		rc = SUCCESS;
	}
	else
	{
		rc = ERROR_COULD_NOT_REGISTER_DRIVER;
	}
	
	return rc;
}

struct bus_driver* require_driver(bus_driver_type_t type)
{
	struct bus_driver *driver = NULL;

	if (check_for_driver(type))
	{
		drivers[type].ref_count++;
		driver = drivers[type].driver;
	}

	return driver;
}

void release_driver(bus_driver_type_t type)
{
	if (check_for_driver(type))
	{
		if (drivers[type].ref_count > 0)
		{
			drivers[type].ref_count--;
		}
	}
}

