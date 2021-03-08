# Manual control of servomotors
## Introduction
Servomotors are intelligent actuators capable of maintaining a position controlled by a PWM type input signal. For a first approach to the topic you can refer to the page [*Servomotor test project*](../lpc1769_servo).
## General system architecture
The project provides for the manual control of 6 servomotors with an LPC1769 development board, by means of 6 PWM channels. The desired position of the servomotors is adjusted thanks to 6 potentiometers, one for each servomotor. In this way, by mounting the servomotors on a mechanical structure such as an artificial arm, an operator can control the position of the same with 6 degrees of freedom; by alternating different positions of the motors, the operator can make the mechanical arm perform a series of simple movements.
This system represents a first step towards the development of a fully automated arm, capable of replicating more or less complex trajectories recorded during a learning period under the guidance of an external operator.
## Assembly plan
The complete circuit is presented in the following image. It should be noted that the power supply of the servomotors, shown as a pack of 4 stylus batteries in series, can obviously be obtained from a bench generator, set between 4.8V and 6V. The power supply of the microcontroller board is connected to the same reference of the power supply for the motors by means of a black cable for joining the grounds.
<p align="center">
  <img src="pic/servo_manual_bb.png" width=800/>
</p>

### Adjustment section
The ends of the servo motor control potentiometers are connected one to the microcontroller power supply (3.3V) and the other to the ground of the development board. The central pins of potentiometers Pot#1 to Pot#6 are connected to the input channels of the microcontroller's 12bit integrated analog to digital converter (A/D). Note that the converter channels AD0.1 to AD06 are used, corresponding to pins P0[24], P0[25], P0[26], P1[30], P1[31] and P0[3].
