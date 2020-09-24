# 7-segment display management
The tutorial provides instructions for driving a 7-segment display consisting of two side-by-side digits. The acquired skills will allow to use this simple output device as a data visualization tool for a subsequent exercise.
## Introduction
The 7-segment displays are a simple but effective output device for displaying numbers or (some) letters. The ease of use linked to the simplicity of understanding the technology used (LED) allows the student to learn clearly what is proposed, creating a useful basis for future exercises in which it is necessary to view results in the form of data.
## 7-segment display
7-segment displays are the simplest and oldest display devices; despite this they are still widely used both for educational purposes and in particular applications where the need for high visibility makes the use of this technology useful. In our case the device consists of a set of LEDs mounted in such a way as to form two digits according to the following figure:
<p align="center">
  <img src="pic/2digits-off.png" width=400/>
</p>
Even if we talk about a 7-segment display, actually inside it we find 8 LEDs for each digit (7 that make up the digit plus one that lights up the decimal point). We note from the wiring diagram that the LEDs of the same digit have the anode in common while the cathodes are in common for corresponding segments in the two digits (A-A, B-B, ...). The particular architecture requires connecting one of the two anodes (pin 9 for digit 1 or pin 4 for digit 2) to the high logic level (about 3V) and then to place the current limiting resistors placed at the low logic level (0V) in series with the cathodes of the LEDs we want to turn on (to illuminate the respective segment). Obviously this means that we can only illuminate one digit at a time. How then to illuminate the two figures at the same time? To be precise this would be impossible but it becomes achievable thanks to the slowness of the human eye. In fact, if we manage to turn on the figures in different instants but very close to each other (high frequency) our eye does not notice the trick and we have the feeling that the two figures are on at the same time. Let's take an example: let's say our goal is to display the number 34. It is made up of two digits: 3 (segments A-B-C-D-G) and 4 (segments B-C-F-G). Then we must first power pin 9 (common anode figure 1) and ground the resistors of pins 10, 8, 1, 5, 7 (cathodes segments A-B-C-D-G).
<p align="center">
  <img src="pic/2digits-3.png" width=400/>
</p>
Then we have to interrupt the power supply to pin 9 (turning off the LEDs of digit 1) and power pin 4 (common anode digit 2) and then set the resistors of pins 8, 1, 6, 7 to ground (cathodes segments B-C-F-G).
<p align="center">
  <img src="pic/2digits-4.png" width=400/>
</p>
We note that all this can also be achieved with simple manual switches (apart from the impossibility of obtaining in this way frequencies such as to deceive our eye).

## Used material
* Development board for LPC1769 with expansion connectors
* USB cable for connection to PC
* Development station with LPCXpresso
* Software project lpc1769_7seg
* 1 breadboard
* 7-segment 2-digit display
* 8 limiting resistors of about 3.3 kΩ
* 2 PNP transistors type BC557B
* 2 basic transistor control resistors of about 10kΩ
* connection cables from breadboard
## Assembly diagram
The following figure shows the assembly diagram of the proposed exercise:
<p align="center">
  <img src="pic/7-segmenti_bb.png" width=800/>
</p>
