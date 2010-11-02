
extern struct bus_driver *i2c_driver;

int main()
{
	/* first register all drivers */
	register_driver(BUS_DRIVER_I2C, i2c_driver);

	/* secondly register all modules */
	register_module(fahrprogramm_module);
}
