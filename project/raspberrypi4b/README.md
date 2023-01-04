### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

GPIO Pin: INT GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(tsl2561 REQUIRED)
```

#### 2.4 INT Pin

INT pin need a 4.3KΩ resistor connect to 5V.

### 3. TSL2561

#### 3.1 Command Instruction

1. Show tsl2561 chip and driver information.

   ```shell
   tsl2561 (-i | --information)
   ```

2. Show tsl2561 help.

   ```shell
   tsl2561 (-h | --help)
   ```

3. Show tsl2561 pin connections of the current board.

   ```shell
   tsl2561 (-p | --port)
   ```

4. Run tsl2561 register test.

   ```shell
   tsl2561 (-t reg | --test=reg) [--addr=<VCC | GND | FLOAT>]
   ```

5. Run tsl2561 read test, num is test times.

   ```shell
   tsl2561 (-t read | --test=read) [--addr=<VCC | GND | FLOAT>] [--times=<num>]
   ```

6. Run tsl2561 interrupt test, num is test times, m is the interrupt mode and it can be "00"-"15", low is the interrupt low threshold, high is the interrupt high threshold.

   ```shell
   tsl2561 (-t int | --test=int) [--addr=<VCC | GND | FLOAT>] [--times=<num>] [--mode=<m>] [--low-threshold=<low>] [--high-threshold=<high>]
   ```

7. Run tsl2561 read function, num is read times.

   ```shell
   tsl2561 (-e read | --example=read) [--addr=<VCC | GND | FLOAT>] [--times=<num>]
   ```

8. Run tsl2561 interrupt function, num is read times, m is the interrupt mode and it can be "00"-"15", low is the interrupt low threshold, high is the interrupt high threshold.

   ```shell
   tsl2561 (-e int | --example=int) [--addr=<VCC | GND | FLOAT>] [--times=<num>] [--mode=<m>] [--low-threshold=<low>] [--high-threshold=<high>]
   ```

#### 3.2 Command Example

```shell
./tsl2561 -i

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
./tsl2561 -p

tsl2561: SCL connected to GPIO3(BCM).
tsl2561: SDA connected to GPIO2(BCM).
tsl2561: INT connected to GPIO17(BCM).
```

```shell
./tsl2561 -t reg --addr=FLOAT

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
tsl2561: set interrupt high threshold 17767.
tsl2561: check interrupt high threshold ok.
tsl2561: tsl2561_set_interrupt_low_threshold/tsl2561_get_interrupt_low_threshold test.
tsl2561: set interrupt low threshold 9158.
tsl2561: check interrupt low threshold ok.
tsl2561: finished register test.
```

```shell
./tsl2561 -t read --addr=FLOAT --times=3

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
tsl2561: read lux 316.
tsl2561: read lux 316.
tsl2561: read lux 316.
tsl2561: set integration time 101 ms.
tsl2561: read lux 314.
tsl2561: read lux 314.
tsl2561: read lux 314.
tsl2561: set integration time 402 ms.
tsl2561: read lux 313.
tsl2561: read lux 313.
tsl2561: read lux 313.
tsl2561: set gain 16.
tsl2561: set integration time 13 ms.
tsl2561: read lux 311.
tsl2561: read lux 311.
tsl2561: read lux 311.
tsl2561: set integration time 101 ms.
tsl2561: read lux 311.
tsl2561: read lux 311.
tsl2561: read lux 311.
tsl2561: set integration time 402 ms.
tsl2561: read lux 311.
tsl2561: read lux 311.
tsl2561: read lux 311.
tsl2561: finish read test.
```

```shell
./tsl2561 -t int --addr=FLOAT --times=3 --mode=00 --low-threshold=10 --high-threshold=100

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
tsl2561: read 0x0AE3 and check interrupt.
tsl2561: read 0x0032 and check interrupt.
tsl2561: read 0x0030 and check interrupt.
tsl2561: finish interrupt test.
```

```shell
./tsl2561 -e read --addr=FLOAT --times=3

tsl2561: 1/3.
tsl2561: read is 654 lux.
tsl2561: 2/3.
tsl2561: read is 660 lux.
tsl2561: 3/3.
tsl2561: read is 701 lux.
```

```shell
./tsl2561 -e int --addr=FLOAT --times=3 --mode=00 --low-threshold=10 --high-threshold=100

tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE.
tsl2561: 1/3.
tsl2561: read is 152 lux.
tsl2561: find interrupt.
```

```shell
./tsl2561 -h

Usage:
  tsl2561 (-i | --information)
  tsl2561 (-h | --help)
  tsl2561 (-p | --port)
  tsl2561 (-t reg | --test=reg) [--addr=<VCC | GND | FLOAT>]
  tsl2561 (-t read | --test=read) [--addr=<VCC | GND | FLOAT>] [--times=<num>]
  tsl2561 (-t int | --test=int) [--addr=<VCC | GND | FLOAT>] [--times=<num>]
          [--mode=<m>] [--low-threshold=<low>] [--high-threshold=<high>]
  tsl2561 (-e read | --example=read) [--addr=<VCC | GND | FLOAT>] [--times=<num>]
  tsl2561 (-e int | --example=int) [--addr=<VCC | GND | FLOAT>] [--times=<num>]
          [--mode=<m>] [--low-threshold=<low>] [--high-threshold=<high>]

Options:
      --addr=<VCC | GND | FLOAT>    Set the addr pin.([default: FLOAT])
  -e <read | int>, --example=<read | int>
                                    Run the driver example.
  -h, --help                        Show the help.
      --high-threshold=<high>       Set the interrupt high threshold.([default: 100])
  -i, --information                 Show the chip information.
      --low-threshold=<low>         Set the interrupt low threshold.([default: 10])
      --mode=<m>                    Set the interrupt mode and it can be "00" - "15".([default: 00])
  -p, --port                        Display the pin connections of the current board.
  -t <reg | read | int>, --test=<reg | read | int>
                                    Run the driver test.
      --times=<num>                 Set the running times.([default: 3])
```

