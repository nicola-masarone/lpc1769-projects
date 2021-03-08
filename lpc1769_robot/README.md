# Manual control of servomotors
## Introduction
Servomotors are intelligent actuators capable of maintaining a position controlled by a *PWM* type input signal. For a first approach to the topic you can refer to the page [*Servomotor test project*](../lpc1769_servo).
## General system architecture
The project provides for the manual control of 6 servomotors with an *LPC1769* development board, by means of 6 *PWM* channels. The desired position of the servomotors is adjusted thanks to 6 potentiometers, one for each servomotor. In this way, by mounting the servomotors on a mechanical structure such as an artificial arm, an operator can control the position of the same with 6 degrees of freedom; by alternating different positions of the motors, the operator can make the mechanical arm perform a series of simple movements.
This system represents a first step towards the development of a fully automated arm, capable of replicating more or less complex trajectories recorded during a learning period under the guidance of an external operator.
## Assembly plan
The complete circuit is presented in the following image. It should be noted that the power supply of the servomotors, shown as a pack of 4 AAA batteries in series, can obviously be obtained from a bench generator, set between 4.8V and 6V. The power supply of the microcontroller board is connected to the same reference of the power supply for the motors by means of a black cable for joining the grounds.
<p align="center">
  <img src="pic/servo_manual_bb.png" width=800/>
</p>

### Adjustment section
The ends of the servo motor control potentiometers are connected one to the microcontroller power supply (3.3V) and the other to the ground of the development board. The central pins of potentiometers *Pot#1* to *Pot#6* are connected to the input channels of the microcontroller's 12bit integrated analog to digital converter (A/D). Note that the converter channels *AD0.1* to *AD06* are used, corresponding to pins *P0[24], P0[25], P0[26], P1[30], P1[31]* and *P0[3]*.
### Control section
The servomotors are powered by a separate constant voltage generator between 4.8V and 6V. To simplify the assembly of the 3-wire connectors (yellow, red, black) of the servomotors, a row of 18 pins (3 pins x 6 servomotors) similar to the one shown in the figure can be used.
<p align="center">
  <img src="pic/header.jpg" width=300/>
</p>

By inserting the connector vertically into the breadboard, a simple assembly of the servomotor connectors is then carried out, placing them side by side. The jumper connections are then made on the breadboard for the power supply and the ground of the individual servomotors (red and black cable) to the longitudinal lines connected to the external power supply. Finally, the connections of the commands are made by means of yellow cables that connect respectively the servomotors from *Servo#1* to *Servo#6* to the *PWM* channels which go from *PWM1.1 (P2[0])* to *PWM1.6 (P2[5])*.
## Software
The project code can be downloaded from this same repository. The program foresees the use of two peripherals integrated in the microcontroller: the analog to digital converter (*A/D*), for the acquisition of the command potentiometers, and the *PWM* signal generator, for the servomotors control.
The following figure shows the *main()* function:
<p align="center">
  <img src="pic/main.png" width=900/>
</p>

The settings for the *A/D* converter include the selection of external pins *AD0.1* to *AD0.6*, the setting of continuous conversion at the lowest possible speed and the activation of the interrupt at the end of the conversion for the management of the results. For the *PWM* signal generator, the *PWM1.1* to *PWM1.6* pins are selected, a main period is set at 20ms (from the servomotors datasheet) and a minimum pulse duration value on each servomotor (starting position of the movement).
At the end of the conversion of the *A/D* peripheral, the program jumps into the interrupt handling routine, shown in the following figure:
<p align="center">
  <img src="pic/ADC_IRQ_handler.png" width=650/>
</p>

In the first section the conversion result is extracted (for each channel) with the instruction of the type:

```
((AD0DR1&0xFFFF)
```
Then the current value is averaged with the previous values and assigned to the variable that stores it:

```
ADCvalue1 = (ADCvalue1*(ADC_avg-1) + ((AD0DR1&0xFFFF)))/ADC_avg;
```

In the next section, a value proportional to the reading of the corresponding *A/D* channel is assigned to each *PWM* channel, so that when the potentiometer *n* is in the minimum position the servomotor *n* is in its initial position and when the potentiometer *n* is in the maximum position the servomotor *n* is in its final position.
