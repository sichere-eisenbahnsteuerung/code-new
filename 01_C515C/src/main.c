
int main()
{
	init_driver_subsystem();
	init_module_subsystem();

	/* first register all drivers */
	register_driver(BUS_DRIVER_I2C, i2c_driver);

	/* secondly register all modules */
	register_module(fahrprogramm_module);

	init_all_modules();


	release_all_modules();
}
