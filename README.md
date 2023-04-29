# SPI Simulation Using Bit-banging
SPI_Simulation_Using GPIO<br>
This project using bit-banging technique to simulate SPI protocol<br>

On microcontrollers, peripherals like UART, SPI, I2C, and others are occasionally not pre-set by hardware due of various factors including cost, size, and so on. Therefore, we can configure these communication protocols using software rather than hardware.<br>
This is the reason I decided to learn about the bit-banging standard design of SPI communication on an STM32 microcontroller.<br>

Bit banging is creating the whole series of pulses in software, instead of relying on a piece of hardware inside the microcontroller.<br>
Many microcontrollers have a hardware SPI, and then all you have to do is write a byte to the output register, and the SPI controller will shift the data out, and at the same time receive data from the slave.<br>
You can get an interrupt when the transfer is complete, and then read the received data.

## Master
### Defining the function of GPIO pins
Configuring the state of 4 pins:<br>
• SS: Configuring the pin in Output state.<br>
• SCK: Configuring the pin in Output state.<br>
• MOSI: Configuring the pin in Output state.<br>
• Miso: Configuring the pin in Input state.<br>
### SPI Setup
We will bring the clock signal pin down to low level and the chip select pin up to high level. This is the initial condition when SPI is not yet working.
 ```
void SPI_setup(void){
	SCK_LOW;
	SS_HIGH;
	HAL_Delay(1);
}
```
The purpose of the Delay function is to stabilize the system before starting the data transmission process.
### SPI Begin
To start the SPI communication process, the Master must bring the corresponding Slave's chip select pin down to low logic level. 
Here, only 1 Master and 1 Slave are being used.
```
void SPI_begin(void){
	SS_LOW;
}
```
### SPI Transfer
Using SPI MODE 0, which means CPOL=0; CPHA=0; bitOrder = MSB
```
uint8_t SPI_transfer(uint8_t byte_out){
	uint8_t byte_in = 0;
	uint8_t ibit, res;
	for(ibit = 0x80;ibit>0;ibit = ibit>>1){
		res= byte_out & ibit;
		if(res){
			MOSI_HIGH;
		}
		else {
			MOSI_LOW;
		}
		delay(THalf);
		SCK_HIGH;

		if(read_MISO==HIGH){
			byte_in = byte_in | ibit;
		}
		delay(THalf);
		SCK_LOW;
	}
	return byte_in;
}
```
Algorithm idea:<br>
Since an SPI transmission frame consists of 8 data bits, to retrieve the value of each bit, we use the AND operator in C.

For example:<br>
The character A in binary is 01000001.
|0|1 |1|0|0|0|0|1|
|:----|:----|:----|:----|:----|:----|:----|:----|
|Bit 0|Bit 1|Bit 2|Bit 3|Bit 4|Bit 5|Bit 6|Bit 7|

The MOSI pin will adjust the logic level based on the value of each bit.<br>
To retrieve the value of bit 0, we perform the operation 01100001 & 10000000 and get the result of 0.<br>
Similarly, for the remaining bits, we get either 0 or non-zero result:<br> 
• For the result of 0, the MOSI pin will be brought down to a low logic level.<br>
• For the non-zero result, the MOSI pin will be brought up to a high logic level.<br>
Using a for loop combined with bit shifting 8 times, we can obtain the value of each bit.<br>
```
for(ibit = 0x80;ibit>0;ibit = ibit>>1){
		res= byte_out & ibit;
		if(res){
			MOSI_HIGH;
		}
		else {
			MOSI_LOW;
		}
}
```
When the logic value of MOSI is obtained, we will hold that state for half a cycle, then raise the clock pin to a high level.<br>
At the same time, we will read the pulse value from the MISO pin.<br>
Initialize the byte_in variable with the data type of unint8_t and a default value of 0.<br>
This variable is used to store data sent from the slave.<br>
```
if(read_MISO==HIGH){
    byte_in = byte_in | ibit;
}
```
If the logic value of the MISO pin is at a high level, we will assign that value to each bit of the byte_in variable in each loop using the OR operator. 
If the MISO pin is at a low level, the corresponding bit value of the byte_in variable will always be 0, as we initialized byte_in to be 0.

On the Slave side, the process of sending the character A is performed similarly to the Master side.<br>
• When bit 0 is sent from the Slave to the Master, the MISO pin is at a low level, and the byte_in variable retains its value of 0.<br>
• When bit 1 is sent from the Slave to the Master, the MISO pin is at a high level, and the operation 0000000 | 0100 0000 is performed, at which point the logic value of the MISO pin is at a high level, and the byte_in variable has a value other than 0.<br>
When the value of MISO is obtained, we will continue to hold that state for half a cycle.<br>
Then, we will lower the clock pin to a low level.<br>
This marks the end of a bit transmission process.<br>

### SPI end
This function marks the end of sending 1 byte from the Master to the Slave:
• Lower the SCK pin to a low level.
• Raise the SS pin to a high level.
```
void SPI_end(void){
	SCK_LOW;
	SS_HIGH;
}
```
## Slave
### Defining the functionality for the GPIO pins:
- SS: Configure the pin as Input.
- SCK: Configure the pin as Input.
- MOSI: Configure the pin as Input.
- MISO: Configure the pin as Output.
## SPI Setup
Since it is a Slave, there is no need to configure anything for the Slave in the Setup section.
## SPI Transfer
With a similar algorithm as the one used for the Master, we will also have a function to transfer data from the Slave as follows:
```
uint8_t SPI_transfer(uint8_t byte_out){
	uint8_t byte_in = 0;
	uint8_t ibit, res;

	while(read_SS == HIGH);

	for(ibit = 0x80;ibit>0;ibit = ibit>>1){
		res = (byte_out & ibit );
		if(res){
			MISO_HIGH;
		}
		else {
			MISO_LOW;
		}

		while(read_SCK == LOW);
		if (read_MOSI == HIGH ){
			byte_in = byte_in | ibit;
		}
		while(read_SCK == HIGH);
	}
	return byte_in;
}
```





















