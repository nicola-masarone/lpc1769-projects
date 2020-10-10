# Ultrasonic sensor
## Introduction
<img align="right" src="pic/parkingsensor.jpg" width=200/> Ultrasonic distance measurement has many applications, both in the consumer and industrial fields. In the first case it is enough to think of the vehicle parking sensors while <img align="left" src="pic/tanksensor.jpg" width=200/> in the second case it is possible to refer to the sensor level level sensor in the tanks where physical contact between the sensor and the stored material is not desired.

In general, the distance measurement principle is based on the time it takes for the acoustic signal to travel from the transmitter to the reflective surface and return to the sensor. Knowing the speed (v) of sound propagation in the air and measuring the time (t) it takes, we obtain that the total path (s) of the acoustic wave is:
<p align="center">
  <img src="pic/s_formula.png" width=100/>
</p>

The distance is equal to half of the total distance s, therefore:
<p align="center">
  <img src="pic/d_formula.png" width=130/>
</p>

## The HC-SR04 module
This module integrates an ultrasonic emitter, an ultrasonic receiver and an electronic management part for the generation of a signal with a duration proportional to the echo delay. The document containing some technical specifications provides us with a table with indications of the electrical parameters:
<p align="center">
  <img src="pic/hcsr04_params.png" width=600/>
</p>
