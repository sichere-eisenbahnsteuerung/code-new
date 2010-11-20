
#ifndef _I2C_H_
#define _I2C_H_

#include "../common/types.h"
#include "../common/driver.h"


static int i2c_probe(uint8_t *value, uint32_t len);
static int i2c_shutdown(uint8_t *value, uint32_t len);
static int i2c_send(uint8_t *value, uint32_t len);
static int i2c_recv(uint8_t *value, uint32_t len);


#endif

