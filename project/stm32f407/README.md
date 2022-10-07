### 1. Chip

#### 1.1 Chip Info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

iic pin: SCL/SDA PB8/PB9.

gpio pin: INT PB0.

### 2. Shell

#### 2.1 Shell Parameter

baud rate: 115200.

data bits : 8.

stop bits: 1.

parity: none.

flow control: none.

### 3. TSL2561

#### 3.1 Command Instruction

​          tsl2561 is a basic command which can test all tsl2561 driver function:

​           -i        show tsl2561 chip and driver information.

​           -h       show tsl2561 help.

​           -p       show tsl2561 pin connections of the current board.

​           -t (reg -a (VCC | GND | FLOAT) | read <times> -a (VCC | GND | FLOAT) | int <times> -a (VCC | GND | FLOAT) -m <mode> -th <lowthreshold> <highthreshold>)

​           -t reg -a (VCC | GND | FLOAT)        run tsl2561 register test. 

​           -t read <times> -a (VCC | GND | FLOAT)        run tsl2561 read test. times is test times.

​           -t int <times> -a (VCC | GND | FLOAT) -m <mode> -th <lowthreshold> <highthreshold>        run tsl2561 interrupt test. times is test times.  mode is the interrupt mode and it can be "0"-"15". lowthreshold is interrupt low threshold. highthreshold is interrupt high threshold.

​           -c (read <times>  -a (VCC | GND | FLOAT) | int <times> -a (VCC | GND | FLOAT) -m <mode> -th <lowthreshold> <highthreshold>)

​           -c read <times>  -a (VCC | GND | FLOAT)        run tsl2561 read function. times is read times.

​           -c int <times> -a (VCC | GND | FLOAT) -m <mode> -th <lowthreshold> <highthreshold>        run tsl2561 interrupt function. times is read times.  mode is the interrupt mode and it can be "0"-"15". lowthreshold is interrupt low threshold. highthreshold is interrupt high threshold.

#### 3.2 Command Example

```shell
tsl2561 -i

tsl2561: chip is AMS TSL2561.
tsl2561: manufacturer is AMS.
tsl2561: interface is IIC.
tsl2561: driver version is 2.0.
tsl2561: min supply voltage is 2.7V.
tsl2561: max supply voltage is 3.6V.
tsl2561: max current is 0.60mA.
tsl2561: max temperature is 85.0C.
tsl2561: min temperature is -40.0C.
```

```shell
tsl2561 -p

tsl2561: SCL connected to GPIOB PIN8.
tsl2561: SDA connected to GPIOB PIN9.
tsl2561: INT connected to GPIOB PIN0.
```

```shell
tsl2561 -t reg -a FLOAT

tsl2561: chip is AMS TSL2561.
tsl2561: manufacturer is AMS.
tsl2561: interface is IIC.
tsl2561: driver version is 2.0.
tsl2561: min supply voltage is 2.7V.
tsl2561: max supply voltage is 3.6V.
tsl2561: max current is 0.60mA.
tsl2561: max temperature is 85.0C.
tsl2561: min temperature is -40.0C.
tsl2561: start register test.
tsl2561: tsl2561_set_addr_pin/tsl2561_get_addr_pin test.
tsl2561: set addr pin ADDRESS_GND.
tsl2561: check addr pin ok.
tsl2561: set addr pin ADDRESS_FLOAT.
tsl2561: check addr pin ok.
tsl2561: set addr pin ADDRESS_VCC.
tsl2561: check addr pin ok.
tsl2561: tsl2561_power_down test.
tsl2561: check power down ok.
tsl2561: tsl2561_wake_up test.
tsl2561: check wake up ok.
tsl2561: tsl2561_set_interrupt/tsl2561_get_interrupt test.
tsl2561: check interrupt ok.
tsl2561: check interrupt ok.
tsl2561: tsl2561_set_gain/tsl2561_get_gain test.
tsl2561: set gain 1.
tsl2561: check gain ok.
tsl2561: set gain 16.
tsl2561: check gain ok.
tsl2561: tsl2561_set_integration_time/tsl2561_get_integration_time test.
tsl2561: set integration time 13 ms.
tsl2561: check gain ok.
tsl2561: set integration time 101 ms.
tsl2561: check gain ok.
tsl2561: set integration time 402 ms.
tsl2561: check gain ok.
tsl2561: tsl2561_set_interrupt_mode/tsl2561_get_interrupt_mode test.
tsl2561: set interrupt mode every adc cycle.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode any value out of threshold range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 2 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 3 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 4 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 5 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 6 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 7 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 8 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 9 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 10 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 11 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 12 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 13 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 14 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: set interrupt mode 15 interation time out of range.
tsl2561: check interrupt mode ok.
tsl2561: tsl2561_set_interrupt_high_threshold/tsl2561_get_interrupt_high_threshold test.
tsl2561: set interrupt high threshold 31561.
tsl2561: check interrupt high threshold ok.
tsl2561: tsl2561_set_interrupt_low_threshold/tsl2561_get_interrupt_low_threshold test.
tsl2561: set interrupt low threshold 55400.
tsl2561: check interrupt low threshold ok.
tsl2561: finished register test.
```

```shell
tsl2561 -t read 3 -a FLOAT

tsl2561: chip is AMS TSL2561.
tsl2561: manufacturer is AMS.
tsl2561: interface is IIC.
tsl2561: driver version is 2.0.
tsl2561: min supply voltage is 2.7V.
tsl2561: max supply voltage is 3.6V.
tsl2561: max current is 0.60mA.
tsl2561: max temperature is 85.0C.
tsl2561: min temperature is -40.0C.
tsl2561: start read test.
tsl2561: set gain 1.
tsl2561: set integration time 13 ms.
tsl2561: read lux 55.
tsl2561: read lux 55.
tsl2561: read lux 55.
tsl2561: set integration time 101 ms.
tsl2561: read lux 62.
tsl2561: read lux 62.
tsl2561: read lux 62.
tsl2561: set integration time 402 ms.
tsl2561: read lux 61.
tsl2561: read lux 61.
tsl2561: read lux 61.
tsl2561: set gain 16.
tsl2561: set integration time 13 ms.
tsl2561: read lux 60.
tsl2561: read lux 62.
tsl2561: read lux 60.
tsl2561: set integration time 101 ms.
tsl2561: read lux 61.
tsl2561: read lux 61.
tsl2561: read lux 61.
tsl2561: set integration time 402 ms.
tsl2561: read lux 61.
tsl2561: read lux 61.
tsl2561: read lux 61.
tsl2561: finish read test.
```

```shell
tsl2561 -t int 3 -a FLOAT -m 0 -th 10 100

tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE.
tsl2561: chip is AMS TSL2561.
tsl2561: manufacturer is AMS.
tsl2561: interface is IIC.
tsl2561: driver version is 2.0.
tsl2561: min supply voltage is 2.7V.
tsl2561: max supply voltage is 3.6V.
tsl2561: max current is 0.60mA.
tsl2561: max temperature is 85.0C.
tsl2561: min temperature is -40.0C.
tsl2561: start interrupt test.
tsl2561: irq.
tsl2561: read 0x021D and check interrupt.
tsl2561: irq.
tsl2561: read 0x021C and check interrupt.
tsl2561: irq.
tsl2561: read 0x0222 and check interrupt.
tsl2561: finish interrupt test.
```

```shell
tsl2561 -c read 3 -a FLOAT

tsl2561: 1/3.
tsl2561: read is 67 lux.
tsl2561: 2/3.
tsl2561: read is 65 lux.
tsl2561: 3/3.
tsl2561: read is 66 lux.
```

```shell
tsl2561 -c int 3 -a FLOAT -m 3 -th 10 100

tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_3_INTEGRATION_TIME_OUT_OF_RANGE.
tsl2561: 1/3.
tsl2561: read is 156 lux.
tsl2561: 2/3.
tsl2561: read is 159 lux.
tsl2561: 3/3.
tsl2561: read is 158 lux.
tsl2561: find interrupt.
```

```shell
tsl2561 -h

tsl2561 -i
	show tsl2561 chip and driver information.
tsl2561 -h
	show tsl2561 help.
tsl2561 -p
	show tsl2561 pin connections of the current board.
tsl2561 -t reg -a (VCC | GND | FLOAT)
	run tsl2561 register test.
tsl2561 -t read <times> -a (VCC | GND | FLOAT)
	run tsl2561 read test.times is test times.
tsl2561 -t int <times> -a (VCC | GND | FLOAT) -m <mode> -th <lowthreshold> <highthreshold>
	run tsl2561 interrupt test.times is test times.mode is the interrupt mode and it can be "0"-"15".lowthreshold is interrupt low threshold.highthreshold is interrupt high threshold.
tsl2561 -c read <times> -a (VCC | GND | FLOAT)
	run tsl2561 read function.times is read times.
tsl2561 -c int <times> -a (VCC | GND | FLOAT) -m <mode> -th <lowthreshold> <highthreshold>
	run tsl2561 interrupt function.times is read times.mode is the interrupt mode and it can be "0"-"15".lowthreshold is interrupt low threshold.highthreshold is interrupt high threshold.
```

