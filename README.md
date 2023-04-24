# SPI_Simulation_Using-GPIO
SPI_Simulation_Using GPIO
This project using bit-banging technique to simulate SPI protocol

On microcontrollers, peripherals like UART, SPI, I2C, and others are occasionally not pre-set by hardware due of various factors including cost, size, and so on. Therefore, we can configure these communication protocols using software rather than hardware.
This is the reason I decided to learn about the bit-banging standard design of SPI communication on an STM32 microcontroller.

Bit banging is creating the whole series of pulses in software, instead of relying on a piece of hardware inside the microcontroller.
Many microcontrollers have a hardware SPI, and then all you have to do is write a byte to the output register, and the SPI controller will shift the data out, and at the same time receive data from the slave. You can get an interrupt when the transfer is complete, and then read the received data.

This is pseudo code
```
Make Slave Select low  
Short delay
Do 8 times
  Make the SCK (Serial Clock) pin low 
  Make the MOSI (Master-Out-Slave-In) pin high or low depending on bit 7 of the data  
  Add brief delay  
  Make the SCK output high
  Read MISO (Master-In-Slave-Out) pin
  Shift received data left, and shift the bit just read in as bit 0   
  Add brief delay  
  Shift the data byte 1 bit left
Make Slave Select high again  
```
