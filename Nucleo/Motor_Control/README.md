User Documentation
========
This software is intended to be used with the STM32F303 Nucleo microcontroller.

## Software Requirements
1. The development computer must have the proper device drivers 
installed in order for it to recognize and upload software to the 
Nucleo microcontroller. For Windows, this is the [STSW-LINK009 driver](http://www.st.com/en/development-tools/stsw-link009.html).
2. Install the [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads). This includes the compiler which is used to compile programs for the Nucleo microcontroller.
3. A version of Make should be installed in order to use the provided 
Makefile for program compilation.
4. Clone the project’s [git repository](https://github.com/BCR-Lab/NautiNet). 
This repository contains the source code for the MotorControl class.
5. Download the mbed library from the mbed website. A [copy](mbed.zip) of the library 
is also located in this project’s git repository. This library provides 
functions for controlling the microcontroller hardware.

## Using the MotorControl Class
1. An object of the MotorControl class must first be constructed. 
The constructor requires a pin name parameter and has optional 
parameters for the length of each phase of the cycle, as well as the amplitude.
2. The start() method must first be called to initialize variables.
3. The run() method can then be called repeatedly in a loop to run 
the motor with the set parameters.
4. Parameters can be checked or changed within the user program by 
calling the appropriate class getter and setter methods.

## Compiling and loading software
1. After a program is written, Make should be used to compile the 
software to a binary file which can be loaded onto the Nucleo.
2. When the Nucleo board is plugged into a computer via a USB cable, 
it will appear as an external storage device to the computer. The 
compiled binary file (file type BIN) can then be installed onto the Nucleo using standard 
file copying methods.
