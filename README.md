# guitar_pedal

## Overview
This device is an open source digital effects pedal based on an STM32F405RGT6 microcontroller. 
The pedal comes with 3 preloaded effects: clean, delay and distortion which are selectable via the GUI on the LCD display.
The assembled PCB is available for purchase on my tindie store:
https://www.tindie.com/products/brunohoplite/digital-guitar-effects-pedal/

## Motivation
I designed this pedal because I'm an avid musician and I've been playing the electric guitar for a while. As someone who works in electronics, I felt the need to learn how music effects are created.
This project has been a lot of fun because it was the first time that I went from an idea to a fully functional PCB on my own!
The cool thing about this effects pedal is that it uses an STM32 microcontroller instead of more popular Arduinos. STM32 are powerful microcontrollers and are fairly easy to use.
They come with a free development environment that generates initialization code for the user to start writing his application faster.

## FW
The FW services the rotary knob, the LCD/GUI and the effects. The PCB gives access to the debug interface of the microcontroller for users to write and test their own custom effects.
An St-Link debugger is needed to debug and program the microcontroller.
To get started with the code, download the stm32cubeIDE from ST, import the project and compile it.

## Usage
The pedal comes with 16 by 2 LCD display that lets the user choose and modify each effect using a rotary encoder.
The pedal can be powered via USB or a 9V battery. The schematics of the PCB are in the datasheet.

## Assembled PCB
![Alt text](HW/guitar_pedal_1.jpg?raw=true)
![Alt text](HW/guitar_pedal_2.jpg?raw=true)
