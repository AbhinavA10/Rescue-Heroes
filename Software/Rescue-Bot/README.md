
## Tool Description
-	Arduino Library
-	TaskScheduler library
-	PlatformIO

We’ll be using the STM32 Nucleo-F401RE board. We will use PlatformIO with Arduino libraries

## PlatformIO
We're using PlatformIO to manage our code and board dependancies. Here's the getting started guide: https://docs.platformio.org/en/latest/ide/vscode.html#installation
It:
-	is an extension for VSCode that allows programming and debugging of many uC.
-	Manages libraries and code better than the Arduino IDE
-	Syntax highlighting and autocomplete etc. Has a debugger.
- allows use of Arduino framework and libraries with our board.

The PlatformIO ide provides the build, flash, and serial monitor in the bottom toolbar. The board settings are in the `platformio.ini` file.

## Tasks

Elements of the robot's functionality are broken down into tasks which are run using a cooperative, non-preemptive scheduler (https://github.com/arkhipenko/TaskScheduler).

Tasks are setup in `main.cpp`, and each task has it's own files in the `src/task` folder.

Interrupts will be avoided except for setting flags. Exception is motor encoder interrupts.

## Utilities/Logging Tools
  - Serial.println() on STM32 board will send a message up to PC. Can view this with the Arduino IDE serial plotter
  - PRINT_DEBUG()