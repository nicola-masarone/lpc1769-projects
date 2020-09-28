# Signal acquisition with ADC
The experiment allows the student to develop the skills for the acquisition of a voltage signal by means of an analog-digital converter (ADC), with visualization of the value on a 7-segment display.
## Introduction
Analog-to-digital conversion (ADC) is the technique that allows you to transform an analog signal (continuous in time and amplitude) into a numerical sequence that can be used by the central processor of the microcontroller. The purpose of the experience is to show how the conversion takes place and how to use it to transform a voltage signal into a number. The number obtained will then be displayed on the 7-segment display according to the procedure already seen in the experience of     [7-segment display management](../lpc1769_7seg#7-segment-display-management), to which reference should be made for the entire data display part.
## The analog-to-digital converter (ADC)
An ADC has many features but the most important are certainly: number of bits that express the result of the conversion and maximum conversion speed. These two parameters are, in the case of the LPC1769 microcontroller, equal to 12bit and 200kHz; the first parameter tells us how accurate our conversion is (resolution) while the second parameter (sample rate) tells us how many samples of the signal are converted in one second. We have 8 acquisition channels available for our ADC but in today's experience we will only use one for demonstration purposes.
## Used material
* Development board for LPC1769 with expansion connectors
* USB cable for connection to PC
* Development station with MCUXpresso
* Software project lpc1769_ADC
* 1 breadboard
* 7-segments 2-digits display
* 8 limiting resistors of about 3.3 kΩ
* 2 PNP transistors BC557B type
* 2 transistor's base control resistors of about 10kΩ
* connection cables for breadboard
* a potentiometer of about 20kΩ
* an analog temperature sensor MCP9701 type
## Assembly diagram
For this section, what already seen in the [7-segment display management](../lpc1769_7seg#7-segment-display-management) tutorial is practically repeated, except for the potentiometer or the temperature sensor connected to the ADC converter pin. The following figure shows the assembly diagram of the proposed exercise:
<p align="center">
  <img src="pic/ADC_bb.png" width=800/>
</p>
Translation of the note in the assembly diagram: "the potentiometer can be replaced by the MCP9701 temperature sensor; in this case the yellow wire goes to the central pin of the sensor."
## Potentiometer
The component used to generate an adjustable voltage level is a potentiometer, which is a three-pin adjustable resistor, two extremes seeing the total resistance and a middle seeing a part of the total resistance based on the mechanical adjustment of the slider:
