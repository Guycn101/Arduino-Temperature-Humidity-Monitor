# Arduino Temperature and Humidity Monitor

## Overview

This project implements a simple, real-time temperature and humidity monitoring system using an Arduino Uno (or compatible board), a DHT12 sensor, and an I2C LCD display. The system allows users to turn monitoring on/off via a push button and provides visual (LED) and audible (buzzer) alerts if predefined temperature or humidity thresholds are exceeded.

## Features

* **Real-time Monitoring:** Continuously reads and displays temperature and humidity data.
* **User Control:** Toggle monitoring ON/OFF with a single push button.
* **LCD Display:** Shows current temperature and humidity readings.
* **Threshold Alerts:** Activates an LED and buzzer if temperature exceeds 30°C or humidity exceeds 70%.
* **Serial Output:** Provides status messages via the Serial Monitor for debugging.

## Hardware Components

* Arduino Uno (or compatible board)
* DHT12 Temperature and Humidity Sensor
* I2C LCD Display (16x2 characters, common address 0x27)
* Push Button
* LED
* Buzzer
* Resistors (e.g., 220 Ohm for LED, 10k Ohm for button if not using INPUT_PULLUP)
* Breadboard and Jumper Wires

Here's a basic connection guide:

* **DHT12 Sensor:**
    * VCC to Arduino 5V
    * GND to Arduino GND
    * DATA to Arduino Digital Pin 2 (`dhtPin`)
* **Push Button:**
    * One leg to Arduino Digital Pin 3 (`buttonPin`)
    * Other leg to GND (using `INPUT_PULLUP` on Arduino)
* **LED:**
    * Anode (long leg) to Arduino Digital Pin 4 (`ledPin`) via a 220 Ohm resistor
    * Cathode (short leg) to Arduino GND
* **Buzzer:**
    * Positive (+) to Arduino Digital Pin 5 (`buzzerPin`)
    * Negative (-) to Arduino GND
* **I2C LCD Display:**
    * VCC to Arduino 5V
    * GND to Arduino GND
    * SDA to Arduino A4 (SDA)
    * SCL to Arduino A5 (SCL)

## Software Requirements

This project requires the Arduino IDE and the following libraries:

1.  **DHT sensor library by Adafruit:**
    * Go to `Sketch > Include Library > Manage Libraries...` in Arduino IDE.
    * Search for "DHT sensor library" by Adafruit and install it.
    * You might also need the "Adafruit Unified Sensor" library as a dependency; install it if prompted.
2.  **LiquidCrystal I2C by Frank de Brabander:**
    * Go to `Sketch > Include Library > Manage Libraries...` in Arduino IDE.
    * Search for "LiquidCrystal I2C" and install the one by Frank de Brabander (version 1.1.2 or higher is usually reliable).

## How to Use

1.  **Connect Hardware:** Assemble your components according to the wiring diagram above.
2.  **Open in Arduino IDE:** Open the `TemperatureMonitor.ino` file in the Arduino IDE.
3.  **Install Libraries:** Ensure both `DHT sensor library` and `LiquidCrystal I2C` libraries are installed (see "Software Requirements" above).
4.  **Select Board & Port:** Go to `Tools > Board` and select "Arduino Uno" (or your specific board). Then go to `Tools > Port` and select the correct serial port for your Arduino.
5.  **Upload Code:** Click the "Upload" button (right arrow icon) in the Arduino IDE to compile and upload the code to your Arduino board.
6.  **Operation:**
    * Upon power-up, the LCD will display "System Ready!".
    * Press the button to start monitoring. The LCD will show "Monitoring..." and begin displaying temperature and humidity.
    * If temperature exceeds 30°C or humidity exceeds 70%, the LED will light up and the buzzer will sound.
    * Press the button again to pause monitoring. The LCD will show "System Paused".

## Troubleshooting

* **LCD not showing anything:** Double-check I2C wiring (SDA/SCL, VCC/GND) and the I2C address (default 0x27, but some modules use 0x3F or others. You can use an I2C scanner sketch to find the correct address).
* **DHT readings are `NaN`:** Ensure DHT sensor is correctly wired, and the correct `DHTTYPE` is defined (DHT11, DHT22, or DHT12).
* **Button not responding:** Verify wiring for the button and ensure `INPUT_PULLUP` is correctly used, or add an external pull-up/pull-down resistor.
