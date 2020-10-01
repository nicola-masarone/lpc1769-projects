# LED in sequence with variable speed
The experience involves the use of 8 LEDs to be switched on in sequence with adjustable speed based on the pressure of a button. The skills acquired at the end of the experience include the use of GPIO in input and output, with interrupt management on the input. The system timer is also used with relative management of the interruption for the switching speed of the LEDs.
## Introduction
The experience has as its objective the lighting in sequence of 8 LEDs with adjustable speed based on the pressure of a control button. The skills acquired concern:
+ use of GPIO in input and output;
+ sizing of the driving circuit of an LED;
+ management of a command button by managing the interrupt on inputs;
+ use of the System Tick Timer and its interruptions for the timing of operations
+ use of the LPCXpresso development system for program design, storage and debugging.
+ use of breadboard and development board for LPC1769 for practical tests
## Used material
+ Development board for LPC1769 with expansion connectors
+ USB cable for connection to PC
+ Development station with MCUXpresso
+ Software project lpc1769_LEDs
+ 1 breadboard
+ 8 LEDs
+ 8 limiting resistors of about 1.5 kΩ
+ a breadboard button
+ connection cables from breadboard
## Assembly diagram
The following figure shows the assembly scheme provided for the experience, made with the free Fritzing drawing program:
<p align="center">
  <img src="pic/LEDs_bb.png" width=800/>
</p>
Note that the limiting resistors are 1.5kΩ and the LEDs are all mounted with the cathode (short lead, flat side of the LED) on the ground line of the blue breadboard.

## LED driver circuit design
The analog section relating to the LEDs is made up of a current limiting resistor placed in series with the LED. Everything is powered by the output of the microcontroller's GPIO port, according to the diagram in the following figure:
<p align="center">
  <img src="pic/output_LED_schem.png" width=250/>
</p>
