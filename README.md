# Project2-EmbeddedSystems





Embedded Systems
CSCE 4301 Section 2
Project II Proposal - Liquid level Monitoring System



Submitted by:
Chris Amgad- 900170819
Hassan El Rashidy- 900163312
Mariam Farghaly-900170254

Submitted to:
Dr. Mohamed Shalan
Spring 21















GitHub repo link: 
https://github.com/chrisamgad/Project2-EmbeddedSystems

Project Idea:
The main idea is to develop a liquid level indicator, a simple mechanism to measure the level/depth of liquid inside a container. We will use a pressure sensor to calculate the liquid depth and output high, medium, and low according to the immersion depth of liquid. Nowadays, factories and chemical plants are storing liquids in overhead tanks using pumps. When the water is stored in the tank/container, nobody can recognize an accurate liquid depth down to the bottom of the tank/container. Not tracking the depth of the liquid carefully may result in major problems, and sometimes disasters especially in chemical plants such as having an overflow of toxic liquid in the tank resulting in not just wasting energy and money, but also potentially exposing individuals to danger. To resolve this, we have thought of developing a liquid level monitoring system that generates the liquid depth, where a buzzer will produce a beep sound as an alarm if the depth of the liquid was beyond a specified threshold depth. We will also be sending the current liquid depth to be displayed on a web server constantly to be monitored by a group of engineers in the control room. On a small scale, we will be doing our project on water for simplicity.

Uses:
Check if there is a leakage from a toxic substance.
Maximum Threshold height for liquids are set so that liquids won’t overflow tanks and containers in chemical plants.
Cooling towers use water level indicators to monitor water levels in a tank and make corrective actions based on the level of water. 

Advantages:
Without liquid level indicators in a liquid tank, you would have to manually check whether enough liquid is in the tank, and should your tank ever go below some depth threshold, it could mean your final results may be incorrect, and even sometimes cause disasters. Liquid level indicators allow you to remotely monitor liquid levels and make corrective actions automatically so you can focus on more important issues.
Accurate
Power Saver
Money Saver
Automatic
Water Maximization
Reliable Electronic Design
 
Software to be used:
Keil uVision: Our main code will be running on this application that runs on the microcontroller
Stm32CubeMX: will be using it for the microcontroller configurations 
TeraTerm: will be used for debugging purposes for making sure that the data is being sent correctly from the microcontroller
Arduino IDE: will be used to connect the ESP32 with the webserver where data coming from the microcontroller is displayed
Web browser: will be used to display the final results on esp32 Web Server
Components to be used:
STM32
Pressure Sensor (will be used to calculate the liquid depth)
ESP32
Jumper Wires
Power Supply (USB to Laptop)
Breadboard
USB to TTL
LEDs and/or Buzzer
Languages to be used:
C 
HTML
CSS

Discussion: 
Pressure in liquid =  Density of liquid depth of liquid gravitational field.

Since the gravitational field and density of liquid are constants, we are able to calculate the liquid depth within a container, given that we know the density of a liquid and the gravitational field. Assuming, we’ll be working on water, Water depth can be calculated using the the following formula

Water Depth = (Pressure at some point inside the water - Pressure up at tip of water)/(Density of Water * Gravitational field)  
![WhatsApp Image 2021-04-19 at 3 18 47 AM](https://user-images.githubusercontent.com/68485300/115169360-13b82e00-a0be-11eb-9ab1-f2e01174a4dd.jpeg)


