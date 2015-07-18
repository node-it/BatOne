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

void setup() {
  // Initialize the BatOne board
  BatOne.begin(SDA_PIN, SCL_PIN);
  
  // Serial port for debug
  Serial.begin(115200);
}

void loop() {
  // A variable to hold the return value
  uint32_t batteryStatus;
  
  // Try to read the status of the battery charger
  if (BatOne.readBatteryStatus(&batteryStatus) == BATONE_STAT_OK) {
    // If read was successful, print the result
    Serial.print(F("Battery Charger Status = "));
    Serial.println(batteryStatus); 
  }
  delay(5000);
}

