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

#include <Wire.h>
#include <BatOne.h>

#define SDA_PIN      2
#define SCL_PIN      14

void setup()
{
  // Initialize the BatOne board
  BatOne.begin(SDA_PIN, SCL_PIN);

  // Serial port for debug
  Serial.begin(115200);
}

void loop()
{
  // A variable to hold the return value
  uint32_t batteryStatus;
  static uint32_t oldBatteryStatus = 0xffaa;
  float batteryLevel;
  static float oldBatteryLevel = 0;

  // Read the current battery voltage
  batteryLevel = BatOne.readBatteryVoltage(0.2106);

  // Try to read the status of the battery charger
  if (BatOne.readBatteryStatus(&batteryStatus) == BATONE_STAT_OK &&
      batteryStatus != oldBatteryStatus) {
    oldBatteryStatus = batteryStatus;
    // If read was successful, print the result
    if (batteryStatus & BATONE_PG_MASK) {
      Serial.print(F("Power is good "));
    } else {
      Serial.print(F("Power is bad "));
    }
    if (!(batteryStatus & (BATONE_CHARGING_MASK | BATONE_CHARGE_COMPLETE_MASK))) {
      Serial.print(F(", No battery connected !"));
    } else {
      if (batteryStatus & BATONE_CHARGING_MASK) {
        Serial.print(F(", Battery is charging"));
      }
      if (batteryStatus & BATONE_CHARGE_COMPLETE_MASK) {
        Serial.print(F(", Battery has been charged"));
      }
    }
    Serial.println();
  }

  // Print battery voltage if it has changed from previous round.
  if (abs(batteryLevel - oldBatteryLevel) > 0.01) {
    Serial.print(F("Battery Voltage: "));
    Serial.print(batteryLevel);
    Serial.println(F(" volts"));
    oldBatteryLevel = batteryLevel;
  }
  delay(250);
}

