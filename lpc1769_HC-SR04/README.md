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
This module integrates an ultrasonic emitter, an ultrasonic receiver and an electronic management part for the generation of a signal with a duration proportional to the echo delay. The [document](hcsr04.pdf) containing some technical specifications provides us with a table with indications of the electrical parameters:
<p align="center">
  <img src="pic/hcsr04_params.png" width=600/>
</p>

The power supply and therefore the input/output logic levels are at 5V, which must be kept in mind when using the LPC1769 microcontroller which operates at 3.3V

The module pinout is shown in the following figure:
<p align="center">
  <img src="pic/hcsr04_pinout.png" width=150/>
</p>

where, apart from the obvious meaning of *Vcc* and *GND*, *Trig* represents the input pin to provide the measurement start command while *Echo* is the output pin, on which we read an impulse of duration proportional to the measured time.

The working signals of the module are shown in the following image:
<p align="center">
  <img src="pic/hcsr04_signal.png" width=600/>
</p>

To start the measurement, it is necessary to send a TTL pulse (5V) with a duration of at least 10μs on the Trig pin and then wait for the response, from which the time elapsed for the echo return is obtained. If an excessive time elapses (about 12ms, greater than that expected for the maximum distance of 4m), the measurement is considered invalid.
