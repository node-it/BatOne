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

#ifndef __GUARD_BATONE_H__
#define __GUARD_BATONE_H__

#include <Wire.h>

enum batOneStat_t {
	BATONE_STAT_OK
};

#define	BATONE_PG_MASK              0x01
#define BATONE_CHARGE_COMPLETE_MASK 0x02
#define BATONE_CHARGING_MASK        0x04
#define BATONE_HIGH_CURRENT_MASK    0x08
// The following formula corresponds to the resistor network between the
// battery and the analog input of the ESP8266.
#define DIVIDER_NETWORK             (10000.0 / (10000.0 + 39000.0))

class BatOneClass
{
  public:
	BatOneClass();
	void begin();
	void begin(uint8_t _sda, uint8_t _scl);
	uint32_t readBatteryStatus(uint32_t *result);
	float readBatteryVoltage(float divider = DIVIDER_NETWORK);
	uint32_t enableHighChargeCurrent(void);
	uint32_t disableHighChargeCurrent(void);
  private:
	uint8_t currentState;
};

extern BatOneClass BatOne;

#endif // __GUARD_BATONE_H__
