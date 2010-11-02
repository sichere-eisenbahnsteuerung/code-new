
struct module fahrprogramm_module = 
{
	.name		= "fahrprogramm",
	.init		= fahrprogramm_init,
	.release	= fahrprogramm_release,
	.work		= fahrprogramm_work,
};

struct bus_driver *i2c_driver = NULL;

int fahrprogramm_init(void)
{
	i2c_driver = require_driver(I2C_DRIVER);

	return 0;
}

int fahrprogramm_release(void)
{
	release_driver(I2C_DRIVER);

	return 0;
}

int fahrprogramm_work(void)
{
	uint8_t data[] = { 0x1, 0x3, 0x3, 0x7 };
	i2c_driver->send(data, 4);
}
