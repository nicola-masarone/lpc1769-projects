# Constant speed stepper motor
## Introduction
Stepper motors are motors with discretized stepping motion. For their control it is necessary to use square wave signals suitably out of phase with each other. During the generation of the phase sequence, the motor executes the steps and stops when the sequence ends, maintaining the position with a certain resisting torque (determined by the size of the motor and by the current present in its windings). To power the motor it is necessary to use a power driver (in our case the L298 device) since the current to be supplied to the windings exceeds the output capacity of the microcontroller pins.
## Nema 17HS13-0404S motor
The stepper motor used is of the ***Nema 17HS13-0404S*** type<img align="right" src="pic/quimat.png" width=120/>, bipolar with 12V power supply and a working current of 0.4A. The datasheet of this type of motor can be downloaded (for example) from the [*Osmtec*](http://www.osmtec.com/nema_17_step_motor_17_hs.htm) company link or directly from the [*local copy in pdf format*](17hs.pdf) on this site.

The dimensional characteristics of the motor are briefly summarized in the figure below:
<p align="center">
  <img src="pic/dimensions.png" width=400/>
</p>

In particular we note that the motor has a step angle of 1.8 ° which means that for a complete rotation the motor must take 200 steps (360°/1.8°) in *full-step* mode.

The data of the motor in question are shown in the following image (last row of the table):
<p align="center">
  <img src="pic/17HS13-0404S.png" width=600/>
</p>

The power supply voltage (12V) and current data for each phase (0.4A) should be noted. The resistance of each phase is 30 Ohm (12V/0.4A). The motor is of the bipolar type and therefore has 4 connection wires, as shown in the following figure:
<p align="center">
  <img src="pic/bipolar-4wires.png" width=200/>
</p>

On the datasheet we also find the driving sequence for the full-step and half-step modes (following image):
<p align="center">
  <img src="pic/sequence.png" width=400/>
</p>

We note that in the firmware project the motor phases will be named A +, A-, B +, B- with A- corresponding to C and B- corresponding to D. In this way we will indicate for the first winding a positive terminal A + and a negative A- and for the second winding a positive terminal B + and a negative terminal B-.

## L298 power driver

<img align="left" src="pic/driverL298N.png" width=150/> A module based on the L298 integrated circuit was used for the power driver. The characteristics of the module (very widespread) can be found for example on the [*RobotStore*](https://www.robotstore.it/Controllo-motori-con-driver-L298N-per-motori-DC-e-motori-passo-passo) website while the integrated datasheet is available on the manufacturer's website (ST Microelectronics) at the following address: [*L298*](https://www.st.com/en/motor-drivers/l298.html)

The module is also supplied with a 5V voltage regulator useful for powering the board with microcontroller. It should be noted that this regulator can be used only if the general power supply voltage of the module is contained within 12V. Remember that the power dissipated by the 5V linear regulator is equal to the difference between its input voltage (12V) and output voltage (5V) multiplied by the current supplied. Assuming an absorbed current of 100mA for the development board for LPC1769, we have a dissipated power on the regulator equal to:
<p align="center">
  <img src="pic/formula.png" width=250/>
</p>

We note that the 5V regulator has the cooling fin directly welded on the small printed circuit, with consequent limited possibility of dissipation.

From the following figure we can derive the connections to be made to connect the module to the stepper motor and the microcontroller.
<p align="center">
  <img src="pic/L298N.png" width=600/>
</p>

*Image legend translation: 1. "+" connector for DC motor A or "A +" for stepper motor
    2. "-" connector for DC motor A or "A-" for stepper motor
    3. 12V jumper - remove the jumper if you are using a power supply voltage higher than 12V; this enables the 5V voltage regulator
    4. Motor power supply connector (max 35V) - remove the 12V jumper (# 3) if the voltage is> 12V
    5. GND
    6. 5V output if the 12V jumper is in position; suitable for powering an Arduino board
    7. Jumper for the activation of the DC motor A; keep the jumper in place if using a stepper motor. Connect to PWM output to enable DC motor speed control.
    8. IN1
    9. IN2
    10. IN3
    11. IN4
    12. Jumper for the activation of the DC motor B; keep the jumper in place if using a stepper motor; connect to PWM output to enable DC motor speed control
    13. "+" connector for DC motor B or "B +" for stepper motor
    14. "-" connector for DC motor B or "B-" for stepper motor*

In particular, phase A of the motor must be connected to pins 1-2 (A + black, A- green) while phase B must be connected to pins 13-14 (B + red, B- blue). The 12V input power supply to the module is connected to pin 4, the ground to pin 5. Pin 6 supplies the 5V voltage for the microcontroller board. Note that the mass of the microcontroller board must be combined with that of the module.

## Assembly plan
Pins 7 and 12 are connected with fixed 5V jumpers to always enable the two H bridges of the L298 integrated circuit. The four input pins 8-11 receive the phase signals from the microcontroller output pins: P2.1 to p2.4.

The overall circuit is therefore the following:
<p align="center">
  <img src="pic/stepper_bb.png" width=600/>
</p>

For those wondering why the wiring starts from P2.1 and not from P2.0, the answer is very simple: the choice was obligatory, as pin P2.0 of the development board was damaged (:confounded:).

## The firmware
The project code is in this same repository.

### The *main()* function
<p align="center">
  <img src="pic/main.png" width=800/>
</p>

