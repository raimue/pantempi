/*
 * temphum
 *
 * Copyright (c) 2011 Daniel Berenguer <dberenguer@usapiens.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 11/31/2011
 *
 * Device:
 * Temperature sensor
 * Dual Temperature + Humidity sensor
 * Dual Pressure + Temperature sensor
 *
 * Description:
 * This sketch can generate three different devices depending on the
 * definition of a pre-compiler contstant in sensor.h (only enable one
 * of these options):
 *
 * TEMP: Device measuring temperature from a TMP36 sensor.
 * Pins: PIN_ADCTEMP (ADC input) and PIN_PWRTEMP (power pin)
 *
 * TEMPHUM: Device measuring temperature and humidity from a DHT11/DHT22
 * sensor. In case you use a DHT11 sensor, you will need this library:
 * http://arduino.cc/playground/Main/DHT11Lib
 *
 * Pins: DHT_DATA (digital I/O) and PIN_PWRDHT (power pin)
 *
 * TEMPPRESS: Device measuring temperature and barometric pressure from
 * an I2C BMP085 sensor. This sketch makes use of Adafruit's BMP085 library
 * for Arduino: http://learn.adafruit.com/bmp085/using-the-bmp085
 * Pins: I2C port and PIN_PWRPRESS (Power pin)
 *
 * These devices are low-power enabled so they will enter low-power mode
 * just after reading the sensor values and transmitting them over the
 * SWAP network.
 * Edit sensor.h for your sensor settings (type of sensor and pins)
 *
 * Associated Device Definition Files, defining registers, endpoints and
 * configuration parameters:
 * temp.xml (Temperature sensor)
 * temphum.xml (Dual Humidity + Temperature sensor)
 * temppress.xml (Dual Pressure + Temperature sensor)
 */

#include <EEPROM.h>
#include "regtable.h"
#include "panstamp.h"

#include "sensor.h"

/**
 * Uncomment if you are reading Vcc from A7. All battery-boards do this
 */
//#define VOLT_SUPPLY_A7

/**
 * LED pin
 */
#define LED_STATUS_PIN               4
#define LED_FAILURE_PIN              3

/**
 * Debug output on serial line
 */
//#define DEBUG_SERIAL

/**
 * setup
 *
 * Arduino setup function
 */
void setup()
{
  int i;

  pinMode(LED_STATUS_PIN, OUTPUT);
  digitalWrite(LED_STATUS_PIN, LOW);

  pinMode(LED_FAILURE_PIN, OUTPUT);
  digitalWrite(LED_FAILURE_PIN, LOW);

#ifdef DEBUG_SERIAL
  Serial.begin(57600);
  Serial.println("temphumpress starting up...");
#endif

  // Initialize sensor pins
  initSensor();

  // Init panStamp
  panstamp.init();

  // Transmit product code
  getRegister(REGI_PRODUCTCODE)->getData();

  // Enter SYNC state
  panstamp.enterSystemState(SYSTATE_SYNC);

  // During 3 seconds, listen the network for possible commands whilst the LED blinks
  for(i=0 ; i<6 ; i++)
  {
    digitalWrite(LED_STATUS_PIN, HIGH);
    delay(100);
    digitalWrite(LED_STATUS_PIN, LOW);
    delay(400);
  }

  // Transmit periodic Tx interval
  getRegister(REGI_TXINTERVAL)->getData();
  // Transmit power voltage
  getRegister(REGI_VOLTSUPPLY)->getData();
  // Switch to Rx OFF state
  panstamp.enterSystemState(SYSTATE_RXOFF);
}

/**
 * loop
 *
 * Arduino main loop
 */
void loop()
{
  int res;

  digitalWrite(LED_STATUS_PIN, HIGH);

#ifdef DEBUG_SERIAL
  Serial.print("Sensor read:");
#endif

  // Transmit sensor data
  getRegister(REGI_SENSOR)->getData();
  // Transmit power voltage
  getRegister(REGI_VOLTSUPPLY)->getData();

  if (dtReturn == 0) {
      digitalWrite(LED_FAILURE_PIN, LOW);
  } else {
      digitalWrite(LED_FAILURE_PIN, HIGH);
  }

#ifdef DEBUG_SERIAL
  Serial.print(" ret=");
  Serial.print(dtReturn);
  Serial.print(" tempval=");
  Serial.print((((((unsigned int) dtSensor[0]) << 8) | dtSensor[1]) * 0.1) - 50);
  Serial.print(" humval=");
  Serial.print(((((unsigned int) dtSensor[2]) << 8) | dtSensor[3]) * 0.1);
  Serial.println("");
#endif

  digitalWrite(LED_STATUS_PIN, LOW);

  // Sleep
  panstamp.goToSleep();
}
