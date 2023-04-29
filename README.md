# SPI Simulation Using Bit-banging
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
## Master
### Định nghĩa chức năng cho các chân GPIO
Cấu hình trạng thái của 4 chân:
•	SS: Cấu hình chân ở trạng thái Output.
•	SCK :  Cấu hình chân ở trạng thái Output.
•	MOSI: Cấu hình chân ở trạng thái Output.
•	Miso:   Cấu hình chân ở trạng thái Input.
### SPI Setup
Ở giai đoạn này, chúng ta sẽ đưa chân tín hiệu clock xuống mức thấp và chân chip select lên mức cao. Đây là điều kiện ban đầu khi SPI chưa làm việc.
 ```
void SPI_setup(void){
	SCK_LOW;
	SS_HIGH;
	HAL_Delay(1);
}
```
Mục đích của hàm Delay là để cho hệ thống ổn định trước khi bắt đầu quá trình truyền dữ liệu.
### SPI Begin
Muốn bắt đầu quá trình truyền nhận SPI, Master phải đưa chân chip select của Slave tương ứng xuống mức tích cực thấp. Ở báo cáo này, chúng em chỉ sử dụng 1 Master và 1 Slave.
```
void SPI_begin(void){
	SS_LOW;
}
```
### SPI Transfer
Ở đây, nhóm em sử dụng MODE 0 của SPI, tức là CPOL=0; CPHASE=0;  bitOder = MSB.
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
Ý tưởng của thuật toán:
Vì một khung truyền của SPI gồm 8 bit dữ liệu, nên mỗi lần muốn lấy giá trị của từng bit, ta sử dụng toán tử AND trong C. 

Ví dụ: 
	Ký tự A chuyển qua binary là 01100001.
|0|1 |1|0|0|0|0|1|
|:----|:----|:----|:----|:----|:----|:----|:----|
|Bit 0|Bit 1|Bit 2|Bit 3|Bit 4|Bit 5|Bit 6|Bit 7|

Chân MOSI sẽ dựa vào giá trị của từng bit để điều chỉnh mức tích cực thấp hoặc cao. Muốn lấy giá trị của bit 0, ta sẽ làm phép toán 01100001 & 10000000 thu được kết quả là 0.
	Tương tự với các bit còn lại, ta sẽ thu được kết quả là 0 hoặc khác 0. Với kết quả 0, chân  MOSI sẽ được đưa xuống mức tích cực thấp. Với kết quả khác 0, chân  MOSI sẽ được đưa lên mức tích cực cao. 
	Sử dụng một vòng lặp for kết hợp với phép dịch bit 8 lần, ta sẽ thu được giá trị của từng bit.
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
Khi đã có được giá trị của MOSI, ta sẽ giữ trạng thái đó trong nửa chu kỳ, sau đó đưa giá trị chân clock lên mức tích cực cao. Đồng thời sẽ đọc giá trị xung từ chân MISO. Khởi tạo biến byte_in với kiểu dữ liệu là unint8_t và có giá trị mặc định là 0. Biến này được sử dụng để chứa dữ liệu từ slave gửi sang.
```
if(read_MISO==HIGH){
    byte_in = byte_in | ibit;
}
```
Nếu giá trị logic của chân MISO ở mức tích cực cao, ta sẽ gán giá trị đó vào từng bit của biến byte_in trong từng vòng lặp của bằng toán tử OR. Còn khi chân MISO ở mức tích cực thấp, thì giá trị bit tương ứng của biến byte_in luôn bằng 0, do ban đầu ta khởi tạo biến byte_in = 0.

Ở bên phía Slave, quá trình gửi kí tự A được thực hiện tương tự như bên Master.
Khi bit 0 được gửi từ Slave qua Master, chân MISO ở mức tích cực thấp, biến byte_in vẫn giữ nguyên giá trị 0.
Khi bit 1 được gửi từ Slave qua Master, chân MISO ở mức tích cực cao, thực hiện phép toán 0000000  |  0100 0000, khi đó giá trị logic của chân MISO ở mức tích cực cao, biến byte_in có giá trị khác 0.
Khi đã có được giá trị của MISO, ta sẽ tiếp tục giữ trạng thái đó trong nửa chu kỳ. Sau đó đưa giá trị của chân clock xuống mức tích cực thấp. 
Kết thúc 1 quá trình truyền nhận bit. 

### SPI end
Hàm này kết thúc truyền 1 byte Master sang Slave:
	  Đưa chân SCK xuống mức tích cực thấp.
	  Đưa chân SS lên mức tích cực cao. 
```
void SPI_end(void){
	SCK_LOW;
	SS_HIGH;
}
```


























