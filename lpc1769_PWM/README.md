# PWM color LED driving
With this experience, students learn to manage an RGB-type color LED using the PWM control to adjust the intensity of the colors, thus modifying the resulting hue.
## Introduction
An RGB type color LED is basically the union of 3 different colored LEDs: red, green and blue. The driving of the single colors is realized with the PWM outputs of the microcontroller; in this way we can control the luminous intensity of the component colors and thus adjust the overall resulting color.
## The RGB LED
The component used in the experience is shown in the following figure:
<p align="center">
  <img src="pic/LED_RGB.png" width=500/>
</p>

The shorter lead (flat side of the LED head) corresponds to the cathode of the red color; common anode, green cathode and blue cathode follow.
## The PWM (Pulse Width Modulator) peripheral
The PWM can realize square waves with duty-cycle (ratio between the high part of the signal and the repetition period) adjustable from 0% to 100%. Given the type of mounting chosen (common anode of the RGB LED to + VDD) the colors of the LED will turn on during the low part of the signal and will turn off during the high part (logic negated).
More information on the PWM functional block is available on the dedicated page: [*PWM: digital output with analogue possibilities*](PWM_block.md)
## Used material
