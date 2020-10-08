# Liquid crystal display
<img align="left" src="pic/LCD.png" width=100/> In this project the piloting technique of a liquid crystal display (LCD) is presented. We will study how the display segments are switched on by writing a test program for automatic counting from the value 0 to the value 1999.
## Introduction
Liquid Crystal Displays (LCDs) are widely used devices for displaying data. Sometimes these displays are segmented (as in our case) other times they are dot matrix. The former allow the display of digits and characters while the latter can also display images. Segment LCD displays have a similar display to that seen for 7-segment LED displays but have a completely different driving principle; in fact, since they are made with liquid crystals, they must be controlled with alternating voltages to continuously reverse the direction of the current inside the segments. If we did not do this we would have two drawbacks: we would not display anything and we would damage the display irreparably. We add for completeness that there are LCD modules on the market already equipped with internal controller (type HD44780); in this case, the use of the display consists in simply sending appropriate commands to the module which already provides an integrated logic for driving the individual segments.
## 7-segment LCD
<img align="right" src="pic/lcd_struct.png" width=150/> The organization of the segments is shown in the figure to the side. The backplane (indicated in the figure as Common Plane) represents a common reference plane with respect to which all the segments in the foreground of the display are powered. In practice, a segment lights up if the potential at its pin is different from the potential on the backplane pin; the segment is turned off if it has the same potential as the backplane. <img align="left" src="pic/lcd_waveform-static_en.png" width=300/> Since we want the current in the segments to continuously change direction then we will send a square wave signal of suitable frequency (usually above 30Hz to avoid flickering) on the backplane pin and square wave signals with the same frequency on the segment pins, with voltage value equal to the backplane to keep segments off or different value to keep segments on.
From the figure on the side it is clear that the segment lights up (Lit) when the voltage between Common and Segment is different from zero (i.e. when the signal on Common is different from that on Segment). Furthermore, when this happens, the value is alternated so as not to damage the segment.
## Characteristics of the display used
The display used is a 3 1/2 digit, typically used in portable instruments such as multimeter or temperature meter. The extremely small datasheet can be downloaded from [here](JAZZ-EC-NMW.pdf). As you can see, the device has 40 pins, not all used, documented in the following table:
<p align="center">
  <img src="pic/lcd_pinout.png" width=400/>
</p>

The names of the LCD segments corresponding to the pins are shown in another image taken from the datasheet:
<p align="center">
  <img src="pic/lcd_screen.png" width=400/>
</p>

With 3E, for example, the E segment of the digit 3 is indicated; with 2A the segment A of the digit 2. The segments in the digit are organized as in the LED ones, but for convenience we report it in the following figure:
<p align="center">
  <img src="pic/lcd_digit.png" width=100/>
</p>

## Mount on breadboard
