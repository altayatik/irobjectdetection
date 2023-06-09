# IR Object Detection
[![license](https://img.shields.io/badge/license-APGL--3.0-brightgreen?style=flat-square)](https://github.com/altayatik/sparkchallenge/blob/main/LICENSE) 

This Atmega328 MCU script uses Digital Signals from the E18-D80NK Infrared Sensor to detect if an object is in range.

## Optional Wiring:
E18-D80NK to 5V, Digital Pin, GND
Notification LEDs to Digital or Analog Pin, GND

## Operation Modes:
### Object in Range
Normal Operation, Start Countdown for designated time.
### Object Left Range
Starts grace period of designated time for return.
### Time up / Process Interruption
Countdown is up or the object left range prematurely, start a designated timer to before reset.
### End of Operation
Designated cooldown period has ended, return to range and reset the operation.

##License
This script is protected by GNU Affero General Public License v3.0. and The Copyright Law of the United States (Title 17). For details and legal information visit LICENSE.

