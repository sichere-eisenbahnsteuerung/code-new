
struct bus_driver i2c_driver = {
	.name		= "i2c",
	.probe		= i2c_probe,
	.shutdown	= i2c_shutdown,
	.send		= i2c_send,
	.resv		= i2c_recv,
};

static int 
i2c_probe(uint8_t *data, uint32_t len)
{
	return 0;
}

static int 
i2c_shutdown(uint8_t *data, uint32_t len)
{
	return 0;
}

static int 
i2c_send(uint8_t *data, uint32_t len)
{
	return 0;
}

static int 
i2c_recv(uint8_t *data, uint32_t len)
{
	return 0;
}
