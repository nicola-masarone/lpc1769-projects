# Manual control of servomotors
## Introduction
Servomotors are intelligent actuators capable of maintaining a position controlled by a PWM type input signal. For a first approach to the topic you can refer to the page [*Servomotor test project*](../lpc1769_servo).
## General system architecture
The project provides for the manual control of 6 servomotors with an LPC1769 development board, by means of 6 PWM channels. The desired position of the servomotors is adjusted thanks to 6 potentiometers, one for each servomotor. In this way, by mounting the servomotors on a mechanical structure such as an artificial arm, an operator can control the position of the same with 6 degrees of freedom; by alternating different positions of the motors, the operator can make the mechanical arm perform a series of simple movements.
This system represents a first step towards the development of a fully automated arm, capable of replicating more or less complex trajectories recorded during a learning period under the guidance of an external operator.
