/*
 * ----------------------------------------------------------------------------
 *            _____ _           _                   _
 *           | ____| | ___  ___| |_ _ __ ___  _ __ (_) ___
 *           |  _| | |/ _ \/ __| __| '__/ _ \| '_ \| |/ __|
 *           | |___| |  __/ (__| |_| | | (_) | | | | | (__
 *           |_____|_|\___|\___|\__|_|  \___/|_| |_|_|\___|
 *            ____                   _   ____
 *           / ___|_      _____  ___| |_|  _ \ ___  __ _ ___
 *           \___ \ \ /\ / / _ \/ _ \ __| |_) / _ \/ _` / __|
 *            ___) \ V  V /  __/  __/ |_|  __/  __/ (_| \__ \
 *           |____/ \_/\_/ \___|\___|\__|_|   \___|\__,_|___/
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <pontus@sweetpeas.se> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return - Pontus Oldberg
 * ----------------------------------------------------------------------------
 */
#include "BatOne.h"

#define PCA9536_BASE_ADDRESS  (0x41)
#define PCA9536_REG_INP       0
#define PCA9536_REG_OUT       1
#define PCA9536_REG_POL       2
#define PCA9536_REG_CTR       3

BatOneClass::BatOneClass() { }

void BatOneClass::begin()
{
	currentState = 0;

	// First make sure the SELECT bit is cleared
	Wire.beginTransmission(PCA9536_BASE_ADDRESS);
	Wire.write(PCA9536_REG_OUT);
	Wire.write(0x00);
	Wire.endTransmission();

	// Now set the control register
	// Bits 0-2 are inputs, bit 2 is output
	Wire.beginTransmission(PCA9536_BASE_ADDRESS);
	Wire.write(PCA9536_REG_CTR);
	Wire.write(0x07);
	Wire.endTransmission();
	
	// And we need to invert the status bits since
	// are pulled by open drain drivers in the
	// charger device.
	Wire.beginTransmission(PCA9536_BASE_ADDRESS);
	Wire.write(PCA9536_REG_POL);
	Wire.write(0x07);
	Wire.endTransmission();
}

void BatOneClass::begin(uint8_t _sda, uint8_t _scl)
{
	Wire.begin(_sda, _scl);
	begin();
}

uint32_t BatOneClass::readBatteryStatus(uint32_t *result)
{
	uint32_t stat = BATONE_STAT_OK;

	Wire.beginTransmission(PCA9536_BASE_ADDRESS);
	Wire.write(0);
	Wire.endTransmission();

	Wire.requestFrom(PCA9536_BASE_ADDRESS, 1);
	while(!Wire.available());

	*result = (uint32_t)(Wire.read() & 0x0f);

	return stat;
}


uint32_t BatOneClass::enableHighChargeCurrent(void)
{
	uint32_t result = BATONE_STAT_OK;

	// Bits 0-2 are inputs, bit 2 is output
	Wire.beginTransmission(PCA9536_BASE_ADDRESS);
	Wire.write(PCA9536_REG_OUT);
	Wire.write(0x08);
	Wire.endTransmission();

	return result;
}


uint32_t BatOneClass::disableHighChargeCurrent(void)
{
	uint32_t result = BATONE_STAT_OK;

	// Bits 0-2 are inputs, bit 2 is output
	Wire.beginTransmission(PCA9536_BASE_ADDRESS);
	Wire.write(PCA9536_REG_OUT);
	Wire.write(0x00);
	Wire.endTransmission();

	return result;
}

// Create an instance of the library
BatOneClass BatOne;

// EOF
