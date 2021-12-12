# GREENHOUSE MONITORING AND CONTROL SYSTEM <br />"THE AUTOGARDENER 3000 👨‍🌾✂️🌳"

### Team members

* Jesús Borobia (responsible for code and sensors)
* Valentin Cristea (responsible for actuators and working principle)
* Cosma Teodor Mihai (responsible for xxx)
* Radu Balc (responsible for xxx)

Link to this file in your GitHub repository:

https://github.com/CristeaValentin/Digital-electronics-2/blob/main/DE2%20GREENHOUSE%20PROJECT/DE2%20PROJECT.md

### Table of contents

* [Project objectives](#objectives)
* [Hardware description](#hardware)
* [Libraries description](#libs)
* [Main application](#main)
* [Video](#video)
* [References](#references)

<a name="objectives"></a>

## Project objectives

Our project aims to provide the user with a way to automate the daily routine of wattering the plants and ensuring the best conditions for them to grow. Our greenhouse monitoring and control system gathers information from his sensors (temperature, air humiity, soil humidity, light intensity) and actuates the devices that provide the plants the best conditions possible for their growth.

You can see below our block diagram:

![Main Diagram](https://github.com/CristeaValentin/Digital-electronics-2/blob/main/DE2%20GREENHOUSE%20PROJECT/flowchart2.png)

You can see below our flowchart diagram for each function:

![Diagram2](https://github.com/CristeaValentin/Digital-electronics-2/blob/main/DE2%20GREENHOUSE%20PROJECT/flowchart1.png)

<a name="hardware"></a>

## Hardware description

**1. ATMEGA328P** - is a high performance, low power controller from Microchip. ATMEGA328P is an 8-bit microcontroller based on AVR RISC architecture. It is the most popular of all AVR controllers as it is used in ARDUINO boards.

**2. Sensors:**
* Temperatude and humidity sensor - we use I²C connection protocol to write and read the informations from the sensor.
* Soil humidity sensor - we use I²C connection protocol to write and read the informations from the sensor.
* Light intensity sensor - we use an analog system consisting of a fotoresistor in a voltage divider and we interpret the voltage obtained as light intensity levels

**3. Actuators:**
* Relay with DC fan (to control the temperature)
* Relay with Irrigation Pump (to control the soil humidity)
* Relay with Window opener (to control the temperature)
* Relay with Lightbulb (to control the light)

**4. Other Components:**
* LCD Display (HD44780) - used to display information about temperature and air humidity
* 2x 10kΩ resistors, 4x 800Ω resistors
* 4x LEDs to indicate presence of current through the devices
* 24 Volt rail (can be made by two 12V batteries in series)

<a name="libs"></a>

## Libraries description

* gpio.h: For controlling AVR's gpio pins
* lcd.h: For using the LCD module
* timer.h: For defining timers
* uart.h: For using UART communication

<a name="main"></a>

## Main application

You can see our circuit design below:

![Project Circuit](https://github.com/CristeaValentin/Digital-electronics-2/blob/main/DE2%20GREENHOUSE%20PROJECT/projectcircuit1.png)

Let us take a look at the functionality of our sensors and actuators.
Below we can see an in depth diagram of the temperature sensor's functionality.

![TempDiagram](https://github.com/CristeaValentin/Digital-electronics-2/blob/main/DE2%20GREENHOUSE%20PROJECT/flowchart3.png)

Below we can see an in depth diagram of the humidity sensor's functionality:

![SoilDiagram](https://github.com/CristeaValentin/Digital-electronics-2/blob/main/DE2%20GREENHOUSE%20PROJECT/flowchart4.png)

Below we can see an in depth diagram of the light intensity sensor's functionality:

![LightDiagram](https://github.com/CristeaValentin/Digital-electronics-2/blob/main/DE2%20GREENHOUSE%20PROJECT/flowchart5.png)

<a name="video"></a>

## Video

Write your text here

<a name="references"></a>

## References

1. https://learn.adafruit.com/i2c-addresses/the-list
2. https://riunet.upv.es/bitstream/handle/10251/75797/SANCLEMENTE%20-%20DISEÑO%20DE%20CASA%20DOMÓTICA%20CONTROLADA%20POR%20ARDUINO.pdf?sequence=5
3. https://create.arduino.cc/projecthub/billy-king/mini-greenhouse-1-20x0-60x0-60-f43bcc?ref=tag&ref_id=greenhouse&offset=1
4. https://nevonprojects.com/greenhouse-monitoring-and-control-system-using-iot-project/
