# Project2- Tank Water level Monitoring System

GitHub repo link: 
https://github.com/chrisamgad/Project2-EmbeddedSystems

Folder containing Presentation and slides link:
https://drive.google.com/drive/folders/1Xi24b90M7S0XWpfNvOQFmxRoCfGsfB9i

Demo Prototype 1:
https://drive.google.com/file/d/1AlHKBb-8y5lhWUE6whyIiaD2Bf_UlwFG/view?usp=sharing

Embedded Systems
<br/>
CSCE 4301 Section 2
<br/>
Project II Proposal
<br/>
`Spring 21`


### Submitted by Group #4:
* Chris Amgad- 900170819
* Hassan El Rashidy- 900163312
* Mariam Farghaly-900170254

## Submitted to:
Dr. Mohamed Shalan

## Project Idea:
The main idea is to develop a tank water level indicator, a simple mechanism to measure the level/depth of water inside a tank. We will use a pressure sensor to calculate the water depth and output depth according to the immersion depth of water. Nowadays, water is stored in the tank/container, nobody can recognize an accurate water depth down to the bottom of the tank/container. Not tracking the depth of the water carefully may result in major problems. To resolve this, we have thought of developing a tank water liquid level system that generates the water depth, where a buzzer will produce a beep sound as an alarm if the depth of the water was beyond a specified threshold depth. We will also be sending the current water depth to be displayed on a web server constantly to be monitored by a group of engineers in the control room. On a small scale, we will be doing our project on water for simplicity.

## Advantages:
* Without water level indicators in a water tank, you would have to manually check whether enough water is in the tank, and should your tank ever go above a level threshold, it could mean your final results may be incorrect, and even sometimes cause disasters. Tank water level indicators allow you to remotely monitor the water level and take corrective actions automatically so you can focus on more important issues.
* Accurate
* Power Saver
* Money Saver
* Automatic
* Water Maximization
* Reliable Electronic Design
***
 
## Software to be used:

* Keil uVision: Our main code will be running on this application that runs on the microcontroller
* Stm32CubeMX: will be using it for the microcontroller configurations 
* TeraTerm: will be used for debugging purposes for making sure that the data is being sent correctly from the microcontroller
* Arduino IDE: will be used to connect the ESP32 with the web server where data coming from the microcontroller is displayed
* Web browser: will be used to display the final results on esp32 Web Server

***

## Components to be used:

* STM32
* MS5540C Sensor (will be used to calculate the liquid depth)
* ESP32
* Jumper Wires
* Power Supply (USB to Laptop)
* Breadboard
* USB to TTL
* LEDs and/or Buzzer

***

## Languages to be used:
* C 
* HTML
* CSS

***

## Initial Design: 
![Screenshot_7](https://user-images.githubusercontent.com/42348385/115172829-554cd700-a0c6-11eb-97b2-e963fa8659d4.png)

Since the gravitational field and density of liquid are constants, we are able to calculate the liquid depth within a container, given that we know the density of a liquid and the gravitational field. Assuming, we’ll be working on water, Water depth can be calculated using the following formula. <br/>
![Screenshot_8](https://user-images.githubusercontent.com/42348385/115172917-7a414a00-a0c6-11eb-9a41-e3cb5a8d04bb.png)
![WhatsApp Image 2021-04-19 at 3 54 19 AM](https://user-images.githubusercontent.com/68485300/115169360-13b82e00-a0be-11eb-9ab1-f2e01174a4dd.jpeg)

## Technical Challenges
* Applying the melted wax without damaging the sensor to isolate all the metal contacts
* Welding the metal without damaging the white gel
* The isolation chemical affects the connections to the sensor since the connected wires would slip off constantly
* Longer wires affected the results
## Current Status
* We have developed a tank water level system that monitors the water level successfully, sending out depth results on Teraterm.

## Next Milestone
* Connect the ESP32 with the web server where data coming from the microcontroller
* Display final results webserver on ESP32 webserver
* Complete the wiki page
