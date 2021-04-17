# Variable speed stepper motor
## Introduction
In the previous project [*constant speed stepper motor*](https://github.com/nicola-masarone/lpc1769-projects/tree/master/lpc1769_step_motor) we have introduced a type of control by using a *Timer* for the motor steps sequence. The speed of the *Timer* has been set to a constant value, thus determining a rectangular speed profile for the stepper motor's speed. We have already concluded that having such a speed profile represents a limit, since to avoid losing steps it is necessary to limit the motor rotation speed a lot. In the following image we review the point of the *firmware* code of the previous project where we set the constant speed of the *stepper* motor:
<p align="center">
  <img src="pic/main_red.png" width=600/>
</p>

obtaining a rectangular speed profile as shown in the following figure:
<p align="center">
  <img src="pic/vel_step.png" width=200/>
</p>

The objective of the current project is the realization of a speed profile for the trapezoidal stepper motor, with constant and predetermined acceleration and deceleration. The result we intend to obtain is represented in the following figure:
<p align="center">
  <img src="pic/vel_trapez.png" width=200/>
</p>

## Hardware
