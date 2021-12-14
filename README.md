# GREENHOUSE MONITORING AND CONTROL SYSTEM <br />"THE AUTOGARDENER 3000 👨‍🌾✂️🌳"

### Team members

* Jesús Borobia (responsible for code and sensors)
* Valentin Cristea (responsible for actuators and working principle)
* Cosma Teodor Mihai (responsible for flow charts and state diagrams)
* Radu Balc (responsible for Github page and documentation)

Link to our in GitHub repository:

https://github.com/CristeaValentin/GreenHouseProject

### Table of contents

* [Project objectives](#objectives)
* [Hardware description](#hardware)
* [Libraries description](#libs)
* [Main application](#main)
* [Video](#video)
* [References](#references)

<a name="objectives"></a>

## Project objectives

Our project aims to provide the user with a way to automate the daily routine of watering the plants and ensuring the best conditions for them to grow. Our greenhouse monitoring and control system gathers information from his sensors (temperature, air humidity, soil humidity, light intensity) and actuates the devices that provide the plants the best conditions possible for their growth.

You can see below our block diagram:

![Main Diagram](https://github.com/CristeaValentin/GreenHouseProject/blob/main/Images/P%C3%A1gina%201.png)

You can see below our flowchart diagram for each function:

![Diagram2](https://github.com/CristeaValentin/GreenHouseProject/blob/main/Images/flowcharts.png)

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
* 2x 10kΩ resistors, 4x 800Ω resistors, 1x 300Ω resistor
* 4x LEDs to indicate presence of current through the devices
* 24 Volt rail (can be made by two 12V batteries in series)

<a name="libs"></a>

## Libraries description

While implementing our code, we used several libraries from the previous laboratory exercises of this semester.
<br />Our **main.c** file is [here](https://github.com/CristeaValentin/GreenHouseProject/blob/main/GreenHouseSimulation/GreenHouseSimulation/main.c) and you can access the libraries that we used below. You can see the details and the code of the libraries using the **Doxygen aplication**.

* [gpio.h](https://htmlpreview.github.io/?https://github.com/CristeaValentin/GreenHouseProject/blob/main/html/gpio_8h.html): For controlling AVR's gpio pins
* [lcd.h](https://htmlpreview.github.io/?https://github.com/CristeaValentin/GreenHouseProject/blob/main/html/lcd_8h.html): For using the LCD module
* [timer.h](https://htmlpreview.github.io/?https://github.com/CristeaValentin/GreenHouseProject/blob/main/html/timer_8h.html): For defining timers
* [uart.h](https://htmlpreview.github.io/?https://github.com/CristeaValentin/GreenHouseProject/blob/main/html/uart_8h.html): For using UART communication
* [twi.h](https://htmlpreview.github.io/?https://github.com/CristeaValentin/GreenHouseProject/blob/main/html/twi_8h.html): For I2C communication

<a name="main"></a>

## Main application

You can see our circuit design below:

![Project Circuit](https://github.com/CristeaValentin/Digital-electronics-2/blob/main/DE2%20GREENHOUSE%20PROJECT/projectcircuit1.png)

Let us take a look at the functionality of our sensors and actuators.
Below we can see an in depth diagram of the temperature sensor's functionality.

![TempDiagram](https://github.com/CristeaValentin/GreenHouseProject/blob/main/Images/P%C3%A1gina%202.png)

Below we can see an in depth diagram of the humidity sensor's functionality:

![SoilDiagram](https://github.com/CristeaValentin/GreenHouseProject/blob/main/Images/P%C3%A1gina%203.png)

Below we can see an in depth diagram of the light intensity sensor's functionality:

![LightDiagram](https://github.com/CristeaValentin/GreenHouseProject/blob/main/Images/P%C3%A1gina%204.png)

<a name="video"></a>

## Video

![](https://github.com/CristeaValentin/GreenHouseProject/blob/main/Images/GREENHOUSEGIF.gif)

[Here](https://www.youtube.com/watch?v=9WtXB5z8xvI) you can find the video presentation of our project in which you will find informations about the present state of the project, application, block diagram, components, and future improvements that we can make.

[Here](https://www.youtube.com/watch?v=U2p7m7lnoyg) you can find the in depth simulation video of uor project, where you can see how our project works in detail.

<a name="references"></a>

## References

1. [I2C addresses](https://learn.adafruit.com/i2c-addresses/the-list)
2. [GreenHouse inspiration Nr.1](https://create.arduino.cc/projecthub/billy-king/mini-greenhouse-1-20x0-60x0-60-f43bcc?ref=tag&ref_id=greenhouse&offset=1)
3. [GreenHouse inspiration Nr.2](https://nevonprojects.com/greenhouse-monitoring-and-control-system-using-iot-project/)
