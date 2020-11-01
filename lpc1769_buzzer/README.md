# Overview
The project realizes the driving of a [*CEP-2242*](cep-2242.pdf) buzzer by means of a *PWM* signal. In this mode it is possible to manage both the volume of the sound (by acting on the *duty-cycle*) and on the frequency of the sound (by modifying the period). The buzzer is controlled by a PNP [*BC557B*](BC556.pdf) type BJT, supplied in the *Embedded Artists* development kit. Use of the BJT avoids requiring excessive current to the microcontroller port.
## Test wiring diagram
In the following drawing we report the wiring diagram of the buzzer driven by the transistor in turn controlled by a switch able to supply 0V or 3V to its base.
<p align="center">
  <img src="pic/buzzer_schem.png" width=400/>
</p>

When the diverter is moved upwards (3V) a voltage equal to that on the emitter arrives at the base of the transistor (also connected directly to 3V): in this way the voltage v<sub>BE</sub> is equal to zero, the transistor is disabled and does not let the current pass through the buzzer which is therefore off. Moving the diverter downwards (0V) a potential difference is created between the base and the emitter which settles around -0.7V ÷ -0.8V: the transistor goes into conduction supplying current to the buzzer which begins to sound. Resistor R1 serves to limit the base current to a value of approximately:
<p align="center">
  <img src="pic/ib_formula.png" width=300/>
</p>

Note that the current has a positive direction from the base towards the diverter (*PNP* type *BJT*).

The proposed circuit allows you to test the buzzer without the development board of the microcontroller, also giving the possibility to measure the currents and voltages involved.
## Test assembly plan
The circuit test assembly layout is shown in the following drawing:
<p align="center">
  <img src="pic/buzzer_bb_test.png" width=600/>
</p>

To replace the two 1.5V batteries, we can connect an external 3V regulated power supply or use the development board which provides a voltage of about 3.3V.

Now try to measure the collector current and the base current when the buzzer sounds. Would it have been prudent to connect the buzzer directly to the microcontroller, eliminating the BJT?
