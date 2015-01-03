/**
 * sensor.h
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
 * Creation date: 09/01/2012
 */

#ifndef _SENSOR_H
#define _SENSOR_H

#include <Arduino.h>

/**
 * Type of sensor. Uncomment only one of these options: TEMP, TEMPHUM or TEMPPRESS
 */
//#define TEMP  1          // Temperature sensor (TMP36)
#define TEMPHUM  1         // Temperature + Humidity sensor (DHT11 or DHT22)
//#define TEMPPRESS  1     // Temperature + Pressure sensor = BMP085

#ifdef TEMPHUM
//#define DHT11  1           // Temperature + Humidity sensor = DHT11
#ifndef DHT11
#define DHT22  1           // Temperature + Humidity sensor = DHT22
#endif
#endif

/**
 * Sensor values
 */
#ifdef TEMP
extern byte dtSensor[2];
#elif TEMPHUM
extern byte dtSensor[4];
#else
extern byte dtSensor[6];
#endif
extern byte dtReturn;

/**
 * Sensor reading function
 */
#if defined(TEMP)
int sensor_ReadTemp(void)
#elif defined(TEMPHUM)
int sensor_ReadTempHum(void);
#elif defined(TEMPPRESS)
int sensor_ReadTempPress(void);
#endif

/**
 * Sensor initialization
 */
void initSensor(void);

/**
 * Pin definitions
 */

/**
 * Uncomment if you are reading Vcc from A7. All battery-boards do this
 */
#define VOLT_SUPPLY_A7

// Temperature + Humidity (DHT11 or DHT22)
#ifdef TEMPHUM
#define PORTW_DHT_DATA    PORTD
#define PORTR_DHT_DATA    PIND
#define PORTD_DHT_DATA    DDRD
#define BIT_DHT_DATA      6
#define PIN_DHT_DATA      6

#define setDataPin()      bitSet(PORTW_DHT_DATA, BIT_DHT_DATA)
#define clearDataPin()    bitClear(PORTW_DHT_DATA, BIT_DHT_DATA)
#define getDataPin()      bitRead(PORTR_DHT_DATA, BIT_DHT_DATA)
#define setDataInput()    bitClear(PORTD_DHT_DATA, BIT_DHT_DATA)
#define setDataOutput()   bitSet(PORTD_DHT_DATA, BIT_DHT_DATA)

#define PIN_PWRDHT        5
#define dhtSensorON()     digitalWrite(PIN_PWRDHT, HIGH);
#define dhtSensorOFF()    digitalWrite(PIN_PWRDHT, LOW);

// Temperature + Pressure (BMP085)
#elif TEMPPRESS
#define PIN_PWRPRESS      15   // Digital pin
#define pressSensorON();  digitalWrite(PIN_PWRPRESS, HIGH);
#define pressSensorOFF(); digitalWrite(PIN_PWRPRESS, LOW);

// Temperature only (TMP36)
#elif TEMP
#define PIN_ADCTEMP       2    // Analog pin
#define PIN_PWRTEMP       15   // Digital pin
#define tempSensorON();   digitalWrite(PIN_PWRTEMP, HIGH);
#define tempSensorOFF();  digitalWrite(PIN_PWRTEMP, LOW);
#endif

#endif

