# Rescue-Bot
MTE 380 Rescue-Bot for the Fall 2021 [MTE 380](http://www.ucalendar.uwaterloo.ca/1819/COURSE/course-MTE.html#MTE380) Mechatronics Engineering Design Workshop course. 
The project was to build an autonomous robot that could navigate through a search & rescue course (shown in gif below), avoiding traps and hazards, to locate, retrieve, and bring a Lego person to safety (green zones).

> [Click here](https://youtu.be/ztVF_HEkW2k) for full Youtube video of our robot completing the search and rescue course!

[![](./images/Animation.gif)](https://youtu.be/ztVF_HEkW2k)

# Team Members

| Team Member      	| Role                         	|
|------------------	|------------------------------	|
| Abhinav Agrahari 	| Electrical and Firmware Lead 	|
| Kyle Tam         	| Mechanical Lead              	|
| Daniel Leung     	| Project Manager              	|
| Liam Clark       	| Software Developer           	|

# Renders

![](./images/render2.jpg)
![](./images/render3.jpg)

# Electrical Diagrams

- datasheets, high-level block diagram, KiCAD schematics

## Electrical Block Diagram

### Microcontrollers
- `STM32F401RE` Nucleo board --> main microcontroller
- `Arduino Nano` --> Dedicated servo driver
### Sensors
Sensor interfacing and signal conditioning/classification is implemented for the following sensors:
- 4x `TCS34725` Color Sensors, multiplexed
- `MPU6050` IMU
- Motor Encoders - [`DG10D-E`](https://www.sparkfun.com/products/16413)
### Actuators
- Hobby servo - `MG995`
- 2x Hobby motors - [`DG10D-E`](https://www.sparkfun.com/products/16413)

![](./Electrical/Block-Diagram/Block_Diagram.svg)

## Schematic
Schematic made using KiCad
![](./Electrical/Rescue-bot/Rescue-bot-schematic.svg)

# Software

Bare-metal firmware using C++.

The firmware structure is based on 'state machines' and co-operative 'tasks'. Firmware for our robot was written using PlatformIO, enabling use of the Arduino framework for SMT32 Nucleo board.

The firmware for STM32 Nucleo board is located [here](./Software/Rescue-Bot). See it's README for more info about the STM32 project.

## Testing
Color data from various parts of the Search and Rescue course were collected with all color sensors, then plotted in 3D RGB space. Our color classification uses a Euclidean distance thresholding algorithim.
![](./Software/Computer_Colour_Visualization/Spheres/spheres_adafruit_edit.png)
![](./Software/Computer_Colour_Visualization/Spheres/spheres_ebay_edit.png)

Motor speed is controlled via PID feedback loop, tuned through heruistic methods

Motor encoder velocity readings are filted using a low-pass filter in software to turn this:
![](./images/before_lpf.png)

into a smoother reading like this:
![](./images/after_lpf.png)

# Mechanical Drawings

![](./images/model.png)
![](./images/model_exploded.png)

[PDF of all mechanical drawings](./images/Robot_Assembly_Drawing.pdf)

[![](./images/Solidworks_drawing.png)](./images/Robot_Assembly_Drawing.pdf)
[![](./images/Solidworks_drawing_BOM.png)](./images/Robot_Assembly_Drawing.pdf)
