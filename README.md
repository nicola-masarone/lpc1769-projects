# lpc1769-projects.
Simple projects for lpc1769 microcontroller from NXP.

Each folder beginning with *lpc1769* contains a separate project, with a description either for software either for hardware.

Please note that two folders (*/lpc_board_nxp_lpcxpresso_1769* and */lpc_chip_175x_6x*) contain proprietary software from NXP, as described in their LICENSE files. This software is needed to compile projects in other folders.

+ [*LED in sequence with variable speed*](https://github.com/nicola-masarone/lpc1769-projects/tree/master/lpc1769_LEDs). The experience involves the use of 8 LEDs to be switched on in sequence with adjustable speed, based on the pressure of a button. The skills acquired at the end of this practical include the use of GPIO in input and output, with interrupt management on the input. The system timer is also used with relative management of the interruption for the switching speed of the LEDs.
+ [*7-segment display management*](https://github.com/nicola-masarone/lpc1769-projects/tree/master/lpc1769_7seg). The tutorial provides instructions for driving a 7-segment display consisting of two side-by-side digits. The acquired skills will allow to use this simple output device as a data visualization tool for a subsequent exercise.
+ [*Signal acquisition with ADC*](https://github.com/nicola-masarone/lpc1769-projects/tree/master/lpc1769_ADC). The experiment allows the student to develop the skills for the acquisition of a voltage signal by means of an analog-digital converter (ADC), with visualization of the value on a 7-segment display.
+ [*Rotary encoder*](https://github.com/nicola-masarone/lpc1769-projects/tree/master/lpc1769_QEI). In this experience the rotary encoder (rotary switch) is used to study the operation of the QEI (Quadrature Encoder Interface) present in the LPC1769 microcontroller. The project provides for the reuse of what is already known from the 7-segment display management for the data display section.
+ [*PWM color LED driving*](https://github.com/nicola-masarone/lpc1769-projects/tree/master/lpc1769_PWM). With this experience, students learn to manage an RGB-type color LED using the PWM control to adjust the intensity of the colors, thus modifying the resulting hue.
+ [*Liquid crystal display*](https://github.com/nicola-masarone/lpc1769-projects/tree/master/lpc1769_LCD). In this project the piloting technique of a liquid crystal display (LCD) is presented. We will study how the display segments are switched on by writing a test program for automatic counting from the value 0 to the value 1999.
+ [*Ultrasonic sensor*](https://github.com/nicola-masarone/lpc1769-projects/tree/master/lpc1769_HC-SR04). This project allows the use of the HC-SR04 ultrasonic module to create a distance meter with data display on LCD.
