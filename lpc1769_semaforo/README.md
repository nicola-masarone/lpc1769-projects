# A general look
The project presented here simulates the management of a traffic light intersection with three times: time A for vehicles in one direction, time B for vehicles in the other direction and time P dedicated to pedestrians.
## The assembly plan
The circuit used for the demonstration involves the use of the development board for LPC1769 and an external breadboard with 9 LEDs dedicated to the three user streams of the intersection, according to the assembly diagram shown in the following figure.
<p align="center">
  <img src="pic/semaforo_bb.png" width=700/>
</p>

*Yellow note translation: approximately 1k resistors must be sized according to the LED used*
The groups of LEDs should clearly be duplicated on the sides of the intersection but the management program remains identical. The project code for LPC1769 is reported in this same repository.
## Software analysis
