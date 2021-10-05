# RP2040_PWM Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/RP2040_PWM.svg?)](https://www.ardu-badge.com/RP2040_PWM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/RP2040_PWM.svg)](https://github.com/khoih-prog/RP2040_PWM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/RP2040_PWM/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/RP2040_PWM.svg)](http://github.com/khoih-prog/RP2040_PWM/issues)

---
---

## Table of Contents

* [Why do we need this RP2040_PWM library](#why-do-we-need-this-RP2040_PWM-library)
  * [Features](#features)
  * [Why using hardware-based PWM is better](#why-using-hardware-based-pwm-is-better)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [More useful Information about RP2040 PWM](#more-useful-information-about-RP2040-PWM)
  * [PWM overview](#PWM-overview)
  * [Programmer’s Model](#Programmers-Model)
* [Usage](#usage)
  * [1. Create PWM Instance with Pin, Frequency and dutycycle](#1-Create-PWM-Instance-with-Pin-Frequency-and-dutycycle)
  * [2. Initizlize PWM Instance](#1-Initizlize-PWM-Instance)
* [Examples](#examples)
  * [ 1. PWM_Multi](examples/PWM_Multi)
  * [ 2. PWM_DynamicFreq](examples/PWM_DynamicFreq)
* [Example PWM_Multi](#example-PWM_Multi)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. PWM_Multi on MBED RaspberryPi Pico](#1-PWM_Multi-on-MBED-RaspberryPi-Pico)
  * [2. PWM_Multi on RASPBERRY_PI_PICO](#2-PWM_Multi-on-RASPBERRY_PI_PICO)
  * [3. PWM_DynamicFreq on Nano RP2040 Connect](#3-PWM_DynamicFreq-on-Nano-RP2040-Connect)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [RP2040_PWM library](https://github.com/khoih-prog/RP2040_PWM)

### Features

This PWM-wrapper library enables you to use Hardware-PWM blocks on RP2040-based boards to create and output PWM any GPIO pin. These purely hardware-based PWM channels can generate from very low (lowest is **7.5Hz**) to very high PWM frequencies (in the **MHz** range, up to **62.5MHz**).

---

The most important feature is they're purely hardware-based PWM channels. Therefore, their operations are **not blocked by bad-behaving software functions / tasks**.

This important feature is absolutely necessary for mission-critical tasks. These hardware PWM-channels, still work even if other software functions are blocking. Moreover, they are much more precise (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to control external systems (Servo, etc.) requiring better accuracy.

The [**PWM_Multi**](examples/PWM_Multi) example will demonstrate the usage of multichannel PWM using multiple Hardware-PWM blocks (slices). The 8 independent Hardware-PWM slices are used **to control 8 different PWM outputs**, with totally independent frequencies and dutycycles.

Being hardware-based PWM, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet or Blynk services. You can also have many `(up to 16)` PWM output signals to use.

`The RP2040 PWM block has 8 identical slices. Each slice can drive two PWM output signals, or measure the frequency or duty cycle of an input signal. This gives a total of up to 16 controllable PWM outputs. All 30 GPIO pins can be driven by the PWM block`

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

You'll see `software-based` SimpleTimer is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

---

#### Why using hardware-based PWM is better

Imagine you have a system with a **mission-critical** function, controlling a robot or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware-based PWM channels still work even if other software functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software-based PWMs, using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software-based PWMs, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.


---

### Currently supported Boards

1. RP2040-based boards such as **NANO_RP2040_CONNECT, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. using either [**Arduino-mbed  mbed_nano or mbed_rp2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico core**](https://github.com/earlephilhower/arduino-pico).


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.16+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`ArduinoCore-mbed mbed_nano or mbed_rp2040 core 2.5.2+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino **NANO_RP2040_CONNECT, RASPBERRY_PI_PICO** boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
 3. [`Earle Philhower's arduino-pico core v1.9.5+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**RP2040_PWM**](https://github.com/khoih-prog/RP2040_PWM), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/RP2040_PWM.svg?)](https://www.ardu-badge.com/RP2040_PWM) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**RP2040_PWM**](https://github.com/khoih-prog/RP2040_PWM) page.
2. Download the latest release `RP2040_PWM-master.zip`.
3. Extract the zip file to `RP2040_PWM-master` directory 
4. Copy whole `RP2040_PWM-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**RP2040_PWM** library](https://platformio.org/lib/show/12863/RP2040_PWM) by using [Library Manager](https://platformio.org/lib/show/12863/RP2040_PWM/installation). Search for **RP2040_PWM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)



---
---


## More useful Information about RP2040 PWM

#### PWM overview

From [rp2040-datasheet.pdf](https://datasheets.raspberrypi.org/rp2040/rp2040-datasheet.pdf), page 543

Pulse width modulation (PWM) is a scheme where a digital signal provides a smoothly varying average voltage. This is achieved with positive pulses of some controlled width, at regular intervals. The fraction of time spent high is known as the duty cycle. This may be used to approximate an analog output, or control switchmode power electronics.

The RP2040 PWM block has 8 identical slices. Each slice can drive two PWM output signals, or measure the frequency or duty cycle of an input signal. This gives a total of up to 16 controllable PWM outputs. All 30 GPIO pins can be driven by the PWM block.

<p align="center">
    <img src="https://github.com/khoih-prog/RP2040_PWM/blob/main/pics/PWM_Slice.png">
</p>

Each PWM slice is equipped with the following:

- 16-bit counter
- 8.4 fractional clock divider
- Two independent output channels, duty cycle from 0% to 100% inclusive
- Dual slope and trailing edge modulation
- Edge-sensitive input mode for frequency measurement
- Level-sensitive input mode for duty cycle measurement
- Configurable counter wrap value
- Wrap and level registers are double buffered and can be changed race-free while PWM is running
- Interrupt request and DMA request on counter wrap
- Phase can be precisely advanced or retarded while running (increments of one count)

Slices can be enabled or disabled simultaneously via a single, global control register. The slices then run in perfect lockstep, so that more complex power circuitry can be switched by the outputs of multiple slices.


#### Programmer’s Model

<p align="center">
    <img src="https://github.com/khoih-prog/RP2040_PWM/blob/main/pics/Mappings.png">
</p>

All 30 GPIO pins on RP2040 can be used for PWM:

- The 16 PWM channels (8 2-channel slices) appear on GPIO0 to GPIO15, in the order PWM0_A, PWM0_B, PWM1_A, etc.
- This repeats for GPIO16 to GPIO29. GPIO16 is PWM0 A, GPIO17 is PWM0 B, so on up to PWM6 B on GPIO29
- The same PWM output can be selected on two GPIO pins; the same signal will appear on each GPIO.
- If a PWM B pin is used as an input, and is selected on multiple GPIO pins, then the PWM slice will see the logical OR of those two GPIO inputs


---
---

## Usage

Before using any PWM `slice`, you have to make sure the `slice` has not been used by any other purpose.

#### 1. Create PWM Instance with Pin, Frequency and dutycycle

```
RP2040_PWM* PWM_Instance;

PWM_Instance = new RP2040_PWM(PWM_Pins, freq, dutyCycle);
```

#### 2. Initizlize PWM Instance

```
if (PWM_Instance)
{
  PWM_Instance->setPWM();
}
```

---
---

### Examples: 

 1. [PWM_Multi](examples/PWM_Multi)
 2. [PWM_DynamicFreq](examples/PWM_DynamicFreq). **New**
 
---
---

### Example [PWM_Multi](examples/PWM_Multi)

```
#if ( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || \
      defined(ARDUINO_GENERIC_RP2040) ) && defined(ARDUINO_ARCH_MBED)

  #warning USING_MBED_RP2040_PWM

#elif ( defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || \
        defined(ARDUINO_GENERIC_RP2040) ) && !defined(ARDUINO_ARCH_MBED)

  #warning USING_MBED_RP2040_PWM
#else
  #error This code is intended to run on the RP2040 mbed_nano, mbed_rp2040 or arduino-pico platform! Please check your Tools->Board setting.
#endif

#define _PWM_LOGLEVEL_        1

#include "RP2040_PWM.h"

#define LED_ON        LOW
#define LED_OFF       HIGH

#define pin0    25    // PWM channel 4B
//#define pin0    0   // PWM channel 0A
#define pin1    2     // PWM channel 1A
#define pin2    4     // PWM channel 2A
#define pin3    6     // PWM channel 3A
#define pin4    0     // PWM channel 0A
#define pin5    10    // PWM channel 5A
#define pin6    12    // PWM channel 6A
#define pin7    14    // PWM channel 7A

uint32_t PWM_Pins[]       = { pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7 };

#define NUM_OF_PINS       ( sizeof(PWM_Pins) / sizeof(uint32_t) )

uint32_t dutyCycle[NUM_OF_PINS]  = { 10, 20, 30, 40, 50, 60, 70, 80 };

double freq[] = { 7.50, 8, 10, 1000, 2000, 3000, 8000, 9999 };


RP2040_PWM* PWM_Instance[NUM_OF_PINS];

char dashLine[] = "=============================================================";

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(100);

  Serial.print(F("\nStarting PWM_Multi on ")); Serial.println(BOARD_NAME);
  Serial.println(RP2040_PWM_VERSION);

  Serial.println(dashLine);
  Serial.println("Index\tPin\tPWM_freq\tDutyCycle\tActual Freq");
  Serial.println(dashLine); 

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {   
    Serial.print(index);
    Serial.print("\t"); Serial.print(PWM_Pins[index]);
    Serial.print("\t"); Serial.print(freq[index]);
    Serial.print("\t\t"); Serial.print(dutyCycle[index]);

    PWM_Instance[index] = new RP2040_PWM(PWM_Pins[index], freq[index], dutyCycle[index]);

    if (PWM_Instance[index])
    {
      PWM_Instance[index]->setPWM();

      uint32_t div = PWM_Instance[index]->get_DIV();
      uint32_t top = PWM_Instance[index]->get_TOP();

      Serial.print("\t\t"); Serial.println(PWM_Instance[index]->getActualFreq());
      
      PWM_LOGDEBUG5("\nTOP =", top, ", DIV =", div, ", CPU_freq =", PWM_Instance[index]->get_freq_CPU());
    }
    else
    {
      Serial.println();
    }
  }

  Serial.println(dashLine);
}

void loop()
{
  //Long delay has no effect on the operation of hardware-based PWM channels
  delay(1000000);
}
```
---
---

### Debug Terminal Output Samples

### 1. PWM_Multi on MBED RaspberryPi Pico

The following is the sample terminal output when running example [PWM_Multi](examples/PWM_Multi) on **RaspberryPi Pico**, running [`ArduinoCore-mbed mbed_rp2040 core`](https://github.com/arduino/ArduinoCore-mbed), to demonstrate the ability to provide high PWM frequencies and the accuracy of Hardware-based PWM, **especially when system is very busy**.


```
Starting PWM_Multi on RaspberryPi Pico
RP2040_PWM v1.0.3
=============================================================
Index	Pin	PWM_freq	DutyCycle	Actual Freq
=============================================================
0	25	7.50		10		7.50
1	1	8.00		20		8.00
2	2	10.00		30		10.00
3	3	1000.00		40		1000.00
4	4	2000.00		50		2000.00
5	5	3000.00		60		3000.00
6	6	8000.00		70		8000.00
7	7	9999.00		80		9999.00
=============================================================
```

---

### 2. PWM_Multi on RASPBERRY_PI_PICO

The following is the sample terminal output when running example [**PWM_Multi**](examples/PWM_Multi) on **RASPBERRY_PI_PICO**, running [`Earle Philhower's arduino-pico core`](https://github.com/earlephilhower/arduino-pico), to demonstrate the ability to provide high PWM frequencies and the accuracy of Hardware-based PWM, **especially when system is very busy**.

```
Starting PWM_Multi on RASPBERRY_PI_PICO
RP2040_PWM v1.0.3
=============================================================
Index	Pin	PWM_freq	DutyCycle	Actual Freq
=============================================================
0	25	7.50		10		7.50
1	1	8.00		20		8.00
2	2	10.00		30		10.00
3	3	1000.00		40		1000.00
4	4	2000.00		50		2000.00
5	5	3000.00		60		3000.00
6	6	8000.00		70		8000.00
7	7	9999.00		80		9999.00
=============================================================
```

---

### 3. PWM_DynamicFreq on Nano RP2040 Connect

The following is the sample terminal output when running example [**PWM_DynamicFreq**](examples/PWM_DynamicFreq) on **Nano RP2040 Connect**, running running [`ArduinoCore-mbed mbed_rp2040 core`](https://github.com/arduino/ArduinoCore-mbed), to demonstrate the ability to change dynamically PWM frequencies and the accuracy of Hardware-based PWM.

```
Starting PWM_DynamicFreq on Nano RP2040 Connect
RP2040_PWM v1.0.3
[PWM] _PWM_config.top = 12499 , _actualFrequency = 1000.00
[PWM] PWM enabled, frequency = 1000.00
=============================================================
Change PWM Freq to 2000.00
[PWM] _PWM_config.top = 62499 , _actualFrequency = 2000.00
[PWM] Changing PWM frequency to 2000.00
[PWM] PWM enabled, frequency = 2000.00
Actual PWM Frequency = 2000.00
[PWM] TOP = 62499 , DIV = 1 , CPU_freq = 125000000
Change PWM Freq to 1000.00
[PWM] _PWM_config.top = 12499 , _actualFrequency = 1000.00
[PWM] Changing PWM frequency to 1000.00
[PWM] PWM enabled, frequency = 1000.00
Actual PWM Frequency = 1000.00
[PWM] TOP = 12499 , DIV = 10 , CPU_freq = 125000000
Change PWM Freq to 2000.00
[PWM] _PWM_config.top = 62499 , _actualFrequency = 2000.00
[PWM] Changing PWM frequency to 2000.00
[PWM] PWM enabled, frequency = 2000.00
Actual PWM Frequency = 2000.00
[PWM] TOP = 62499 , DIV = 1 , CPU_freq = 125000000
Change PWM Freq to 1000.00
[PWM] _PWM_config.top = 12499 , _actualFrequency = 1000.00
[PWM] Changing PWM frequency to 1000.00
[PWM] PWM enabled, frequency = 1000.00
Actual PWM Frequency = 1000.00
[PWM] TOP = 12499 , DIV = 10 , CPU_freq = 125000000
Change PWM Freq to 2000.00
[PWM] _PWM_config.top = 62499 , _actualFrequency = 2000.00
[PWM] Changing PWM frequency to 2000.00
[PWM] PWM enabled, frequency = 2000.00
Actual PWM Frequency = 2000.00
[PWM] TOP = 62499 , DIV = 1 , CPU_freq = 125000000
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level `_PWM_LOGLEVEL_` from 0 to 4

```cpp
// Don't define _PWM_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _PWM_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [RP2040_PWM issues](https://github.com/khoih-prog/RP2040_PWM/issues)

---

## TO DO

1. Search for bug and improvement.
2. Similar features for remaining Arduino boards

---

## DONE

1. Basic hardware-based multi-channel PWMs for **RP2040-based boards** such as Nano_RP2040_Connect, RASPBERRY_PI_PICO, etc. using either RP2040 [**ArduinoCore-mbed mbed_nano or mbed_rp2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico core**](https://github.com/earlephilhower/arduino-pico)
2. Add Table of Contents
3. Split `changelog.md`

---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Thanks to [americodias](https://github.com/americodias) to report bugs in 

- [Wrong frequency #1](https://github.com/khoih-prog/RP2040_PWM/issues/1) leading to v1.0.1
- [Change the PWM frequency #2](https://github.com/khoih-prog/RP2040_PWM/issues/2) leading to v1.0.2

<table>
  <tr>
    <td align="center"><a href="https://github.com/americodias"><img src="https://github.com/americodias.png" width="100px;" alt="americodias"/><br /><sub><b>⭐️ Américo Dias</b></sub></a><br /></td>
  </tr>
</table>
  
---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/RP2040_PWM/blob/main/LICENSE)

---

## Copyright

Copyright 2021- Khoi Hoang


