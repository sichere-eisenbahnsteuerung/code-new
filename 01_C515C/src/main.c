
#include "main.h"
#include "common/util.h"
#include "common/driver.h"

#include "drivers/rs232.h"

/*
 * @brief Initialize common stuff for the main program
 */
void init_common(void)
{
	enable_interrupts(1);
    RS232_init();
}


/*
 * @brief The method which gets called initialy by the processor
 */
void main()
{
    uint8_t inp=0;

	init_common();

    RS232_write('t');

    while(1) {
        RS232_work();
        if(RS232_available()) {
            inp = RS232_read();
            RS232_write(inp);  
            RS232_write(inp+1);  
            RS232_write(inp+2);  
            RS232_write(13);    
            RS232_write(10);
        }
    }
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
