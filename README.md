# Project2- Tank Water level Monitoring System

* For this project, we developed a Tank Water level Monitoring System for Embedded systems using STM32CubeMX and Keil μVision running it on the Nucleo-32 board.

***
GitHub repo link: 
https://github.com/chrisamgad/Project2-EmbeddedSystems

Folder containing Presentation and slides link:
https://drive.google.com/drive/folders/1Xi24b90M7S0XWpfNvOQFmxRoCfGsfB9i

Demo Prototype 1:
https://drive.google.com/file/d/1AlHKBb-8y5lhWUE6whyIiaD2Bf_UlwFG/view?usp=sharing

Final Demo:
https://drive.google.com/file/d/1yKsco7V7HbetCimNSc1AXJ9aL4a1K94U/view?usp=drivesdk

***


### Submitted by Group #4:
* Chris Amgad - https://github.com/chrisamgad
* Hassan El Rashidy - https://github.com/HassanELRashidy
* Mariam Farghaly - https://github.com/Mariamfarghaly99

### Submitted to:
Dr. Mohamed Shalan

## Project Statement:
The main idea is to develop a tank water level indicator, a simple mechanism to measure the level/depth of water inside a tank. We use a pressure sensor to calculate the water depth and output depth according to the immersion depth of water. Nowadays, water is stored in the tank/container, nobody can recognize an accurate water depth down to the bottom of the tank/container. Not tracking the depth of the water carefully may result in major problems. To resolve this, we developed a tank water level monitoring system that generates the water depth, where a buzzer produce a beep sound as an alarm if the depth of the water was beyond a specified threshold depth. We send the current water depth to be displayed on a web server constantly to be monitored by a group of engineers in the control room. We connected the ESP32 with the web server where data coming from the microcontroller and displayed final results webserver on ESP32 webserver.

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

## Stm32cube configurations:
![WhatsApp Image 2021-05-25 at 6 43 45 PM](https://user-images.githubusercontent.com/75340968/119536417-5c33cd00-bd89-11eb-9a73-dd5bfb4c78b1.jpeg)

## Languages used:
* C 
* HTML
* CSS
* Ajax

***

## Software Architecture:
This is the flowchart of our system. We donot use FreeRTOS because we didnot need to use it. We had communications between two devices(microcontroller and water level sensor) and then sending our results to the ESP32, so there is no priorities in the tasks.

![Capture3](https://user-images.githubusercontent.com/68485300/119531281-0dcfff80-bd84-11eb-8e6c-cb6f9864e7bb.JPG)

This is the flowchart for pressue reading from the MS5540C Sensor

![Screen Shot 2021-05-25 at 6 28 10 PM](https://user-images.githubusercontent.com/75340968/119536474-681f8f00-bd89-11eb-93ed-417e2008184f.png)

## Hardware Description not covered in lab:

* ESP32

 We used the ESP32 to interface with stm32 microcontroller to display the final results webserver because the ESP32 provides Wi-Fi.
 
![WhatsApp Image 2021-05-25 at 6 06 56 PM](https://user-images.githubusercontent.com/68485300/119532474-34426a80-bd85-11eb-9408-1d1697525cea.jpeg)
* MS5540C Sensor

The MS5540C pressure sensor measures absolute water/ air pressure/ temperature. Thus we used it to measure water depth in water level in tank.
It carries a metal protection cap filled with silicon gel to ensure protection against the water

![Picture1](https://user-images.githubusercontent.com/75340968/119527759-ecb9df80-bd80-11eb-94e4-bd9022257450.png)

* 10 - 1100 mbar absolute pressure range
* 6 coefficients for software compensation stored on-
chip
* Piezoresistive silicon micromachined sensor
* Integrated miniature pressure sensor 6.2 x 6.4 mm
* 16 Bit ADC
* 3-wire serial interface
* 1 system clock line (32.768 kHz)
* Low voltage and low power consumption
* High Endurance (HE version)

## Block Diagram
![WhatsApp Image 2021-05-25 at 5 22 41 PM](https://user-images.githubusercontent.com/75340968/119525363-b9765100-bd7e-11eb-8834-3c9c7e4ca9ce.jpeg)


## Design: 
![Capture](https://user-images.githubusercontent.com/68485300/119531099-e6793280-bd83-11eb-8491-25f5c00927fe.JPG)

Since the gravitational field and density of water are constants, we are able to calculate the liquid depth within a container, given that we know the density of water and the gravitational field. Water depth can be calculated using the following formula. <br/>
![Capture2](https://user-images.githubusercontent.com/68485300/119531135-eda04080-bd83-11eb-8cf8-60900b8f2c9b.JPG)

* Initial pressure= the current pressue before applying water
* Pressure (at the bottom of the cup) = current pressure readings from the MS5540C Sensor
* gravitational field= 9.81 m/s^2
* Density of water= 997 kg/m³ approximately 1000 kg/m³
* PressureDiff=(Pressure-Initial Pressure)*100;        //convertion from millibar(mbar) into pascal
* CurrentDepth=PressureDiff/(1000*9.81);               //current depth in metres
* CurrentDepth=CurrentDepth*100;                       //convertion from metres to centimeter

![Screen Shot 2021-05-25 at 8 20 26 PM](https://user-images.githubusercontent.com/75340968/119548639-b4250080-bd96-11eb-9e64-2bd56af15a82.png)


## Technical Challenges
* Applying the melted wax without damaging the sensor to isolate all the metal contacts
* Welding the metal without damaging the white gel
* The isolation chemical affects the connections to the sensor since the connected wires would slip off constantly
* Longer wires affected the results. -> The solution we have found was to make a hole in the bottom of the cup and insert the water level sensor and ceiling the opening using a sealing wax gun.
* The first captured pressure value (Reference pressure value at the bottom of the beaker) on reset were invalid sometimes --> solution: we added a verification piece of code on reset that checks if the differance between the first and second pressure reading is not a huge number. If the differance between the first and second pressure readings was more than a pre-defined value, Capture the first reading again and repeat verification, else start collecting the pressure values and calculating the depth.

## Demo
* We have developed a tank water level system that monitors the water level successfully, sending out water depth results to be displayed on the webserver using the ESP32 in centimeters.

## Prototype 1 connections
![WhatsApp Image 2021-05-25 at 7 49 45 PM](https://user-images.githubusercontent.com/75340968/119544896-7920ce00-bd92-11eb-8a8d-78cf7424e076.jpeg)

![Screenshot_10](https://user-images.githubusercontent.com/42348385/117244683-ca940800-ae39-11eb-8deb-c070ec77e6c4.png)

## Final Demo connections

![WhatsApp Image 2021-05-25 at 7 54 46 PM](https://user-images.githubusercontent.com/75340968/119545476-25fb4b00-bd93-11eb-972d-18c16b639800.jpeg)

![WhatsApp Image 2021-05-25 at 7 18 59 PM](https://user-images.githubusercontent.com/75340968/119544498-0dd6fc00-bd92-11eb-8665-1a5eb0f48055.jpeg)

![Screen Shot 2021-05-25 at 7 48 35 PM](https://user-images.githubusercontent.com/75340968/119544968-8ccc3480-bd92-11eb-9a56-9ee33d4e272b.png)

## Future Work
For future Engineers, we can include the GSM-based system where the message will be sent to the particular authorized person when the water level is below the required level. 

We believe that our project is beneficial as the world’s water resources become increasingly stressed, so our tank water level monitoring system become more crucial. It is possible for future work to be utilized in a centralized control of all the dams using wireless technology under the control of the government which would be beneficial to the whole country.

## References
* https://cdn.shopify.com/s/files/1/0672/9409/files/water_depth_sensor_MS5540C_Arduino_tutorial.pdf?698
* https://cdn.shopify.com/s/files/1/0672/9409/files/MS5540C_datasheet.pdf?616
* https://store.fut-electronics.com/products/under-water-depth-sensor
* https://www.watelectronics.com/simple-water-level-alarm-circuit/
* https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/uart.html
* https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/protocols/esp_http_server.html
* https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf
* https://www.st.com/resource/en/datasheet/stm32l432kc.pdf
