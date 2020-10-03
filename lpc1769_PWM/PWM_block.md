# PWM: digital output with analogue possibilities
<img align="left" src="pic/pwmLEDs.jpg" width=150/>
The PWM (Pulse Width Modulator) output allows various functions: from the modulation of signals for communications to the power management of LEDs and electric motors. With only two voltage levels available (0V and 3.3V), thanks to the variable duration of the upper and lower parts of the output, the PWM functional block is able to regulate the power supplied from a minimum of 0% to a maximum of 100%, with extreme flexibility.

## PWM technique and its applications
Pulse Width Modulation is a technique that allows the generation of pulses having all the same amplitude but with programmable duration, from a minimum to a predetermined maximum. The uses of PWM are many, from adjusting the light intensity of an LED to adjusting the rotation speed of an electric motor. Here we will refer to the application with LED because it is easy to realize with the available components.
### On/Off management of an LED
From the theory we know that to be turned on an LED must be powered with a voltage higher than the threshold voltage and connected in series to a current limiting resistor; we also know that the light intensity of the LED is proportional to the intensity of the current passing through it. Note the threshold voltage V<sub>D</sub> and the supply voltage V<sub>CC</sub>, we can adjust the intensity of the current I<sub>LED</sub> (and therefore the brightness) with the R<sub>LED</sub> series resistor sized with the following formula:
<p align="center">
  <img src="pic/RLED_formula.png" width=150/>
</p>

If the V<sub>CC</sub> power is supplied by a digital output of the microcontroller (3.3V) then we can only turn on the LED with a preset intensity.
### PWM management of an LED
To modify the luminous intensity of the LED, adjusting it between the maximum value (corresponding to the ILED of the previous formula) and zero, we can apply a square wave with a fixed amplitude (3.3V) and variable duty-cycle; the duty-cycle is the ratio between the duration of the high voltage level and the repetition period of the square wave. In the following figure we see three examples of duty-cycle: at 10%, at 50% and at 90%.
<p align="center">
  <img src="pic/duty_cycle.png" width=300/>
</p>

In this way the LED will turn on at certain times (high voltage level) and will turn off at others (low voltage level). If the alternation of switch-off and switch-on instants is fast enough, our eye will perceive an average light intensity between maximum and minimum, proportional to the duty-cycle. Ultimately, to apply the PWM technique it is necessary to set a signal repetition period and a time interval within this period during which the signal is at the high logic level (the low one derives from it by difference).
