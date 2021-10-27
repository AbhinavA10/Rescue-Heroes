Software Design
-	State machine
-	TaskScheduler library or FreeRTOS
-	PlatformIO
o	
We’ll be using the STM32 Nucleo-F401RE board. This can be programmed via the Arduino IDE, or STM32Cube. Another alternative is PlatformIO
PlatformIO
-	Extension for VSCode that allows programming and debugging of many uC.
-	Manages libraries and code better than the Arduino IDE
-	Syntax highlighting and autocomplete etc. ArduinoIDE is bad. PlatformIO is much better
-	Works with our Nucleo board – can use the Arduino framework, or STM32Cube framework (HAL)
Most likely, we’ll be using PlatformIO with the Arduino framework.

-	State Machine Ideas:
o	Knowing when we're in a hole, so we don't speed into a wall.
