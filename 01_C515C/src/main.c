
#include "main.h"
#include "common/util.h"
#include "common/driver.h"


/*
 * @brief Initialize common stuff for the main program
 */
void init_common(void)
{
	enable_interrupts(1);
}


/*
 * @brief The method which gets called initialy by the processor
 */
void main()
{
	init_common();
	//init_driver_subsystem();
	//init_module_subsystem();

	/* first register all drivers */
	//register_driver(BUS_DRIVER_I2C, i2c_driver);

	/* secondly register all modules */
	//register_module(fahrprogramm_module);

	//init_all_modules();

	/* FIXME work loop */

	//release_all_modules();
}
