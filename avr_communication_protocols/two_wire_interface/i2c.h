#include <avr/io.h>
#include "pinDefines.h"

void initI2C(void);
// sets pullups and initializes bus speed to 100kHz (at FCPU=8MHz)

void i2cWaitToComplete(void);
// waits for the hardware to set the TWINT flag

void i2cStart(void);
// sets TWSTA

void i2cStop(void);
// sets TWSTO

void i2cSend(uint8_t data);
// loads data and sends it out, waiting for completion

uint8_t i2cReadAck(void);
// read from slave, sending ACK when done (set TWEA)

uint8_t i2cReadNoAck(void);
// read from slave, sending NOACK when done (no TWEA)

