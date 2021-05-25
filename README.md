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
* Chris Amgad - https://github.com/chrisamgad
* Hassan El Rashidy - https://github.com/HassanELRashidy
* Mariam Farghaly - https://github.com/Mariamfarghaly99

## Submitted to:
Dr. Mohamed Shalan

## Project Statement:
The main idea is to develop a tank water level indicator, a simple mechanism to measure the level/depth of water inside a tank. We will use a pressure sensor to calculate the water depth and output depth according to the immersion depth of water. Nowadays, water is stored in the tank/container, nobody can recognize an accurate water depth down to the bottom of the tank/container. Not tracking the depth of the water carefully may result in major problems. To resolve this, we have thought of developing a tank water liquid level system that generates the water depth, where a buzzer will produce a beep sound as an alarm if the depth of the water was beyond a specified threshold depth. We send the current water depth to be displayed on a web server constantly to be monitored by a group of engineers in the control room. We connected the ESP32 with the web server where data coming from the microcontroller and displayed final results webserver on ESP32 webserver

## Advantages:
* Without water level indicators in a water tank, you would have to manually check whether enough water is in the tank, and should your tank ever go above a level threshold, it could mean your final results may be incorrect, and even sometimes cause disasters. Tank water level indicators allow you to remotely monitor the water level and take corrective actions automatically so you can focus on more important issues.
* Accurate
* Power Saver
* Money Saver
* Automatic
* Water Maximization
* Reliable Electronic Design
***
 
## Software Components:

* Keil uVision: Our main code runs on this application that runs on the microcontroller
* Stm32CubeMX: used for the microcontroller configurations 
* TeraTerm: used for debugging purposes for making sure that the data is being sent correctly from the microcontroller
* Arduino IDE: used to connect the ESP32 with the web server where data coming from the microcontroller is displayed
* Web browser: Display the final results on ESP32 Web Server

***

## Hardware Components:

* STM32
* MS5540C Sensor (used to calculate the liquid depth)
* ESP32
* Jumper Wires
* Power Supply (USB to Laptop)
* Breadboard
* USB to TTL
* LEDs 
* Buzzer

***

## Software Architecture:
This is the flowchart of our system. We donot use FreeRTOS because we didnot need to use it. We had communications between two devices(microcontroller and water level sensor) and then sending our results to the ESP32, so there is no priorities in the tasks.

## Hardware:

* ESP32
 We used the ESP32 to interface with stm32 microcontroller to display the final results webserver because the ESP32 provides Wi-Fi.

* MS5540C Sensor 
![Uploading Picture1.png…]()

![WhatsApp Image 2021-05-25 at 5 22 41 PM](https://user-images.githubusercontent.com/75340968/119525363-b9765100-bd7e-11eb-8834-3c9c7e4ca9ce.jpeg)


## Languages used:
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
* Longer wires affected the results. -> The solution we have found was to make a hole in the bottom of the cup and insert the water level sensor and ceiling the opening

## Limitations
* Maximum height that can be measured is 8 cm
* We couldn't remove water gradually

## Demo
* We have developed a tank water level system that monitors the water level successfully, sending out depth results on Teraterm.
![Screenshot_1](https://user-images.githubusercontent.com/42348385/117244231-f662be00-ae38-11eb-946f-70bc793ad20c.png)
![Screenshot_10](https://user-images.githubusercontent.com/42348385/117244683-ca940800-ae39-11eb-8deb-c070ec77e6c4.png)

## Future Work
For future Engineers, we can include the GSM-based system where the message will be sent to the particular authorized person when the water level is below the required level. 
We believe that our project is beneficial as the world’s water resources become increasingly stressed, so our tank water level monitoring system become more crucial. It is possible for future work to be utilized in a centralized control of all the dams using wireless technology under the control of the government which would be beneficial to the whole country.

## References
https://cdn.shopify.com/s/files/1/0672/9409/files/water_depth_sensor_MS5540C_Arduino_tutorial.pdf?698
https://cdn.shopify.com/s/files/1/0672/9409/files/MS5540C_datasheet.pdf?616
https://store.fut-electronics.com/products/under-water-depth-sensor
  
