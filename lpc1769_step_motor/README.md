# Constant speed stepper motor
## Introduction
Stepper motors are motors with discretized stepping motion. For their control it is necessary to use square wave signals suitably out of phase with each other. During the generation of the phase sequence, the motor executes the steps and stops when the sequence ends, maintaining the position with a certain resisting torque (determined by the size of the motor and by the current present in its windings). To power the motor it is necessary to use a power driver (in our case the L298 device) since the current to be supplied to the windings exceeds the output capacity of the microcontroller pins.
## Nema 17HS13-0404S motor
The stepper motor used is of the Nema 17HS13-0404S type <img align="right" src="pic/quimat.png" width=120/> , bipolar with 12V power supply and a working current of 0.4A. The datasheet of this type of motor can be downloaded (for example) from the [*Osmtec*](http://www.osmtec.com/nema_17_step_motor_17_hs.htm) company link or directly from the [*local copy in pdf format*](17hs.pdf) on this site.

The dimensional characteristics of the motor are briefly summarized in the figure below:
<p align="center">
  <img src="pic/dimensions.png" width=400/>
</p>

In particular we note that the motor has a step angle of 1.8 ° which means that for a complete rotation the motor must take 200 steps (360 ° / 1.8 °) in full-step mode.
