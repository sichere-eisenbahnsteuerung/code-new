#include "i2c.h"

bus_driver_t i2c_driver = {
	"i2c",
	&i2c_probe, //(uint8_t*, uint32_t),
	*i2c_shutdown,
	*i2c_send,
	*i2c_recv
};

static int i2c_probe(uint8_t *value, uint32_t len)
{
	return 0;
}

static int i2c_shutdown(uint8_t *value, uint32_t len)
{
	return 0;
}

static int i2c_send(uint8_t *value, uint32_t len)
{
	return 0;
}

static int i2c_recv(uint8_t *value, uint32_t len)
{
	return 0;
}
