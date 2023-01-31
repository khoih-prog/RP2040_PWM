# RP2040_PWM Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/RP2040_PWM.svg?)](https://www.ardu-badge.com/RP2040_PWM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/RP2040_PWM.svg)](https://github.com/khoih-prog/RP2040_PWM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/RP2040_PWM/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/RP2040_PWM.svg)](http://github.com/khoih-prog/RP2040_PWM/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


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
  * [2. Initialize PWM Instance](#2-Initialize-PWM-Instance)
  * [3. Set or change PWM frequency or dutyCycle](#3-set-or-change-PWM-frequency-or-dutyCycle)
  * [4. Set or change PWM frequency and dutyCycle manually and efficiently in waveform creation](#4-Set-or-change-PWM-frequency-and-dutyCycle-manually-and-efficiently-in-waveform-creation)
  * [5. Set or change PWM frequency and dutyCycle in PushPull mode](#5-Set-or-change-PWM-frequency-and-dutyCycle-in-PushPull-mode)
  * [6. Important Notes](#6-Important-Notes)
* [Examples](#examples)
  * [ 1. PWM_Multi](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Multi)
  * [ 2. PWM_DynamicFreq](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_DynamicFreq)
  * [ 3. PWM_DynamicDutyCycle](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_DynamicDutyCycle)
  * [ 4. PWM_MultiChannel](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_MultiChannel)
  * [ 5. PWM_Waveform](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Waveform)
  * [ 6. PWM_Waveform_Fast](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Waveform_Fast)
  * [ 7. PWM_DynamicDutyCycle_Int](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_DynamicDutyCycle_Int)
  * [ 8. PWM_Basic](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Basic)
  * [ 9. PWM_StepperControl](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_StepperControl) **New**
  * [10. PWM_manual](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_manual) **New**
  * [11. PWM_SpeedTest](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_SpeedTest) **New**
  * [12. PWM_PushPull](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull) **New**
  * [13. PWM_PushPull_DynamicDC](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull_DynamicDC) **New**
  * [14. PWM_PushPull_DynamicFreq](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull_DynamicFreq) **New**
* [Example PWM_Multi](#example-PWM_Multi)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [ 1. PWM_Multi on MBED RaspberryPi Pico](#1-PWM_Multi-on-MBED-RaspberryPi-Pico)
  * [ 2. PWM_Multi on RASPBERRY_PI_PICO](#2-PWM_Multi-on-RASPBERRY_PI_PICO)
  * [ 3. PWM_DynamicFreq on Nano RP2040 Connect](#3-PWM_DynamicFreq-on-Nano-RP2040-Connect)
  * [ 4. PWM_DynamicDutyCycle on RASPBERRY_PI_PICO](#4-PWM_DynamicDutyCycle-on-RASPBERRY_PI_PICO)
  * [ 5. PWM_MultiChannel on RASPBERRY_PI_PICO](#5-PWM_MultiChannel-on-RASPBERRY_PI_PICO)
  * [ 6. PWM_Waveform on RASPBERRY_PI_PICO](#6-PWM_Waveform-on-RASPBERRY_PI_PICO)
  * [ 7. PWM_Waveform_Fast on RASPBERRY_PI_PICO](#7-PWM_Waveform_Fast-on-RASPBERRY_PI_PICO)
  * [ 8. PWM_manual on RASPBERRY_PI_PICO](#8-PWM_manual-on-RASPBERRY_PI_PICO)
  * [ 9. PWM_SpeedTest on RASPBERRY_PI_PICO](#9-PWM_SpeedTest-on-RASPBERRY_PI_PICO)
  * [10. PWM_PushPull on RASPBERRY_PI_PICO](#10-PWM_PushPull-on-RASPBERRY_PI_PICO)
  * [11. PWM_PushPull_DynamicDC on RASPBERRY_PI_PICO](#11-PWM_PushPull_DynamicDC-on-RASPBERRY_PI_PICO)
  * [12. PWM_PushPull_DynamicFreq on RASPBERRY_PI_PICO](#12-PWM_PushPull_DynamicFreq-on-RASPBERRY_PI_PICO)
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

This PWM-wrapper library enables you to use Hardware-PWM blocks on RP2040-based boards to create and output PWM any GPIO pin. These purely hardware-based PWM channels can generate from very low (lowest is **7.5Hz * (F_CPU/125)**) to very high PWM frequencies (in the **MHz** range, up to **(F_CPU/2) or 62.5MHz**).

This library is using the **same or similar functions** as other FastPWM libraries, as follows, to enable you to **port your PWM code easily between platforms**

 1. [**RP2040_PWM**](https://github.com/khoih-prog/RP2040_PWM)
 2. [**AVR_PWM**](https://github.com/khoih-prog/AVR_PWM)
 3. [**megaAVR_PWM**](https://github.com/khoih-prog/megaAVR_PWM)
 4. [**ESP32_FastPWM**](https://github.com/khoih-prog/ESP32_FastPWM)
 5. [**SAMD_PWM**](https://github.com/khoih-prog/SAMD_PWM)
 6. [**SAMDUE_PWM**](https://github.com/khoih-prog/SAMDUE_PWM)
 7. [**nRF52_PWM**](https://github.com/khoih-prog/nRF52_PWM)
 8. [**Teensy_PWM**](https://github.com/khoih-prog/Teensy_PWM)
 9. [**ATtiny_PWM**](https://github.com/khoih-prog/ATtiny_PWM)
10. [**Dx_PWM**](https://github.com/khoih-prog/Dx_PWM)
11. [**Portenta_H7_PWM**](https://github.com/khoih-prog/Portenta_H7_PWM)
12. [**MBED_RP2040_PWM**](https://github.com/khoih-prog/MBED_RP2040_PWM)
13. [**nRF52_MBED_PWM**](https://github.com/khoih-prog/nRF52_MBED_PWM)
14. [**STM32_PWM**](https://github.com/khoih-prog/STM32_PWM)

---

The most important feature is they're purely hardware-based PWM channels. Therefore, their operations are **not blocked by bad-behaving software functions / tasks**.

This important feature is absolutely necessary for mission-critical tasks. These hardware PWM-channels, still work even if other software functions are blocking. Moreover, they are much more precise (certainly depending on clock frequency accuracy) than other software timers using `millis()` or `micros()`. That's necessary if you need to control external systems (Servo, etc.) requiring better accuracy.

The [**PWM_Multi**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Multi) example will demonstrate the usage of multichannel PWM using multiple Hardware-PWM blocks (slices). The 8 independent Hardware-PWM slices are used **to control 8 different PWM outputs**, with totally independent frequencies and dutycycles.

Being hardware-based PWM, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet or Blynk services. You can also have many `(up to 16)` PWM output signals to use.

`The RP2040 PWM block has 8 identical slices. Each slice can drive two PWM output signals, or measure the frequency or duty cycle of an input signal. This gives a total of up to 16 controllable PWM outputs. All 30 GPIO pins can be driven by the PWM block`

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

You'll see `software-based` SimpleTimer is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in `loop()`, using `delay()` function as an example. The elapsed time then is very unaccurate

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

1. RP2040-based boards such as **NANO_RP2040_CONNECT, RASPBERRY_PI_PICO, RASPBERRY_PI_PICO_W, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. using either [**Arduino-mbed  mbed_nano or mbed_rp2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico core**](https://github.com/earlephilhower/arduino-pico).


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://www.arduino.cc/en/Main/Software). Using `Arduino IDE 2.0.0+` at your own risk.
 2. [`ArduinoCore-mbed mbed_nano or mbed_rp2040 core 3.5.4+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino **NANO_RP2040_CONNECT, RASPBERRY_PI_PICO** boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
 3. [`Earle Philhower's arduino-pico core v2.7.1+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, RASPBERRY_PI_PICO_W, ADAFRUIT_FEATHER_RP2040, ADAFRUIT_ITSYBITSY_RP2040, CYTRON_MAKER_NANO_RP2040, SPARKFUN_PROMICRO_RP2040, CHALLENGER_2040_WIFI_RP2040, ILABS_2040_RPICO32_RP2040, MELOPERO_SHAKE_RP2040, SOLDERPARTY_RP2040_STAMP, UPESY_RP2040_DEVKIT, WIZNET_5100S_EVB_PICO, GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
 
 
---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**RP2040_PWM**](https://github.com/khoih-prog/RP2040_PWM), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/RP2040_PWM.svg?)](https://www.ardu-badge.com/RP2040_PWM) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**RP2040_PWM**](https://github.com/khoih-prog/RP2040_PWM) page.
2. Download the latest release `RP2040_PWM-main.zip`.
3. Extract the zip file to `RP2040_PWM-main` directory 
4. Copy whole `RP2040_PWM-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**RP2040_PWM** library](https://registry.platformio.org/libraries/khoih-prog/RP2040_PWM) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/RP2040_PWM/installation). Search for **RP2040_PWM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

## More useful Information about RP2040 PWM

#### PWM overview

From [rp2040-datasheet.pdf](https://datasheets.raspberrypi.org/rp2040/rp2040-datasheet.pdf), page 543

Pulse width modulation (PWM) is a scheme where a digital signal provides a smoothly varying average voltage. This is achieved with positive pulses of some controlled width, at regular intervals. The fraction of time spent high is known as the duty cycle. This may be used to approximate an analog output, or control switchmode power electronics.

The RP2040 PWM block has 8 identical slices. Each slice can drive two PWM output signals, or measure the frequency or duty cycle of an input signal. This gives a total of up to 16 controllable PWM outputs. All 30 GPIO pins can be driven by the PWM block.

<p align="center">
    <img src="https://github.com/khoih-prog/RP2040_PWM/raw/main/pics/PWM_Slice.png">
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
    <img src="https://github.com/khoih-prog/RP2040_PWM/raw/main/pics/Mappings.png">
</p>

All 30 GPIO pins on RP2040 can be used for PWM:

- The 16 PWM channels (8 x `2-channel slices`) appear on `GPIO0` to `GPIO15`, in the order `PWM0_A`, `PWM0_B`, `PWM1_A`, etc.
- This repeats for `GPIO16` to `GPIO29`. `GPIO16` is `PWM0 A`, `GPIO17` is `PWM0 B`, so on, up to `PWM6 B` on `GPIO29`
- The same PWM output can be selected on two GPIO pins; the same signal will appear on each GPIO.
- If a PWM B pin is used as an input, and is selected on multiple GPIO pins, then the PWM slice will see the logical OR of those two GPIO inputs


---
---

## Usage

Before using any PWM `slice`, you have to make sure the `slice` has not been used by any other purpose.

#### 1. Create PWM Instance with Pin, Frequency and dutycycle

```cpp
RP2040_PWM* PWM_Instance;

PWM_Instance = new RP2040_PWM(PWM_Pins, freq, dutyCycle);
```

---

#### 2. Initialize PWM Instance

```cpp
if (PWM_Instance)
{
  PWM_Instance->setPWM();
}
```

---

#### 3. Set or change PWM frequency or dutyCycle

To use `float new_dutyCycle`

```cpp
PWM_Instance->setPWM(PWM_Pins, new_frequency, new_dutyCycle);
```

such as 

```cpp
dutyCycle = 10.0f;
  
Serial.print(F("Change PWM DutyCycle to ")); Serial.println(dutyCycle);
PWM_Instance->setPWM(pinToUse, frequency, dutyCycle);
```

---

To use `uint32_t new_dutyCycle` = `real_dutyCycle * 1000`

```cpp
PWM_Instance->setPWM_Int(PWM_Pins, new_frequency, new_dutyCycle);
```

such as for `real_dutyCycle = 20%`

```cpp
// dutyCycle = real_dutyCycle * 1000
dutyCycle = 20000;
  
Serial.print(F("Change PWM DutyCycle to ")); Serial.println((float) dutyCycle / 1000);
PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
```

---

#### 4. Set or change PWM frequency and dutyCycle manually and efficiently in waveform creation

Need to call only once for each pin

```cpp
PWM_Instance->setPWM_manual(PWM_Pins, new_top, new_div, new_level);
bool setPWM_DCPercentage_manual(const uint8_t& pin, float& DCPercentage)
```

after that, if just changing `dutyCycle` / `level`, use 

```cpp
// For 50.0f dutycycle
new_level = 50.0f * PWM_Instance->get_TOP() / 100.0f;
PWM_Instance->setPWM_manual(PWM_Pins, new_level);
```

or better and much easier to use

```cpp
new_DCPercentage = 50.0f;
PWM_Instance->setPWM_DCPercentage_manual(PWM_Pins, new_DCPercentage);
```

and the fastest

```cpp
// For 50.0f dutycycle
new_level = 50.0f * PWM_Instance->get_TOP() / 100.0f;
PWM_Instance->setPWM_manual_Fast(pinToUse, dutycycle);
```
---

#### 5. Set or change PWM frequency and dutyCycle in PushPull mode

To use a pair of pins of the same channel / slice. Check [Programmer’s Model](#Programmers-Model)

Need to call only once for each pair of pins

```cpp
float frequency = 2000.0f;
float dutyCycle = 30.0f;

// Pins have to be in pairs of the same PWM slice / channel
// Check https://github.com/khoih-prog/RP2040_PWM#programmers-model
// For example: pins 0/1, 2/3, 4/5, 6/7, 8/9, 10/11, 12/13, 14/15, 16/17, 18/19, 20/21, 22/23, 24/25, 26/27, 28/29

#define pinToUseA      18     // PWM1A
#define pinToUseB      19     // PWM1A

// Use just one of these 2 for a pair
// assigns pinToUseA, with frequency of 200 Hz and a duty cycle of 0%
PWM_Instance = new RP2040_PWM(pinToUseA, frequency, 0);
// assigns pinToUseB, with frequency of 200 Hz and a duty cycle of 0%
//PWM_Instance = new RP2040_PWM(pinToUseB, frequency, 0);
```

after that, if just changing `dutyCycle` / `level`, use 

```cpp
// For 50.0f dutycycle
new_dutyCycle = 50.0f;
PWM_Instance->setPWMPushPull(pinToUseA, pinToUseB, frequency, new_dutyCycle);
```

or if just changing `frequency`, use 


```cpp
// For 50.0f dutycycle
new_frequency = 1000.0f;
PWM_Instance->setPWMPushPull(pinToUseA, pinToUseB, new_frequency, dutyCycle);
```

---

#### 6. Important Notes

##### When using `phaseCorrect == true`

1. the output frequency will be **half** of the input frequency `freq`
2. the init and later usage must be the same `phaseCorrect == true`


```cpp
RP2040_PWM* PWM_Instance;

PWM_Instance = new RP2040_PWM(PWM_Pins, freq, dutyCycle, true);

...

PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle, true);
```

##### When using `phaseCorrect == false`

1. the output frequency will be **equal** of the input frequency `freq`
2. the init and later usage must be the same `phaseCorrect == false`


```cpp
RP2040_PWM* PWM_Instance;

PWM_Instance = new RP2040_PWM(PWM_Pins, freq, dutyCycle);

...

PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
```


---
---

### Examples: 

 1. [PWM_Multi](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Multi)
 2. [PWM_DynamicFreq](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_DynamicFreq)
 3. [PWM_DynamicDutyCycle](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_DynamicDutyCycle)
 4. [PWM_MultiChannel](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_MultiChannel)
 5. [PWM_Waveform](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Waveform)
 6. [PWM_Waveform_Fast](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Waveform_Fast)
 7. [PWM_DynamicDutyCycle_Int](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_DynamicDutyCycle_Int)
 8. [PWM_Basic](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Basic)
 9. [PWM_StepperControl](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_StepperControl) **New**
10. [PWM_manual](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_manual) **New** 
11. [PWM_SpeedTest](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_SpeedTest) **New** 
12. [PWM_PushPull](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull) **New**
13. [PWM_PushPull_DynamicDC](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull_DynamicDC) **New**
14. [PWM_PushPull_DynamicFreq](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull_DynamicFreq) **New**
 
---
---

### Example [PWM_Multi](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Multi)

https://github.com/khoih-prog/RP2040_PWM/blob/57df7e0a3ff7d3ff64e1611e82e593c2f744a20d/examples/PWM_Multi/PWM_Multi.ino#L14-L114


---
---

### Debug Terminal Output Samples

### 1. PWM_Multi on MBED RaspberryPi Pico

The following is the sample terminal output when running example [PWM_Multi](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Multi) on **RaspberryPi Pico**, running [`ArduinoCore-mbed mbed_rp2040 core`](https://github.com/arduino/ArduinoCore-mbed), to demonstrate the ability to provide high PWM frequencies and the accuracy of Hardware-based PWM, **especially when system is very busy**.


```cpp
Starting PWM_Multi on RaspberryPi Pico
RP2040_PWM v1.7.0
=============================================================
Index	Pin	PWM_freq	DutyCycle	Actual Freq
=============================================================
0	25	20.00		10.00		20.00
1	2	30.00		50.00		30.00
2	4	40.00		30.00		40.00
3	6	1000.00		40.00		1000.00
4	0	2000.00		50.00		2000.00
5	10	3000.00		60.00		3000.00
6	12	8000.00		70.00		8000.00
7	14	9999.00		80.00		9999.00
=============================================================

```

---

### 2. PWM_Multi on RASPBERRY_PI_PICO

The following is the sample terminal output when running example [**PWM_Multi**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Multi) on **RASPBERRY_PI_PICO**, running [`Earle Philhower's arduino-pico core`](https://github.com/earlephilhower/arduino-pico), to demonstrate the ability to provide high PWM frequencies and the accuracy of Hardware-based PWM, **especially when system is very busy**.

```cpp
Starting PWM_Multi on RASPBERRY_PI_PICO
RP2040_PWM v1.7.0
=============================================================
Index	Pin	PWM_freq	DutyCycle	Actual Freq
=============================================================
0	25	20.00		10.00		20.00
1	2	30.00		50.00		30.00
2	4	40.00		30.00		40.00
3	6	1000.00		40.00		1000.00
4	0	2000.00		50.00		2000.00
5	10	3000.00		60.00		3000.00
6	12	8000.00		70.00		8000.00
7	14	9999.00		80.00		9999.00
=============================================================

```

---

### 3. PWM_DynamicFreq on Nano RP2040 Connect

The following is the sample terminal output when running example [**PWM_DynamicFreq**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_DynamicFreq) on **Nano RP2040 Connect**, running [`ArduinoCore-mbed mbed_rp2040 core`](https://github.com/arduino/ArduinoCore-mbed), to demonstrate the ability to change dynamically PWM frequencies and the accuracy of Hardware-based PWM.

```cpp
Starting PWM_DynamicFreq on Nano RP2040 Connect
RP2040_PWM v1.7.0
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


### 4. PWM_DynamicDutyCycle on RASPBERRY_PI_PICO

The following is the sample terminal output when running example [**PWM_DynamicDutyCycle**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_DynamicDutyCycle) on **RASPBERRY_PI_PICO**, running [`Earle Philhower's arduino-pico core`](https://github.com/earlephilhower/arduino-pico), to demonstrate the ability to change dynamically PWM dutyCycle and the accuracy of Hardware-based PWM.

```cpp
Starting PWM_DynamicDutyCycle on RASPBERRY_PI_PICO
RP2040_PWM v1.7.0
[PWM] _PWM_config.top = 13299 , _actualFrequency = 1000.00
[PWM] pin =  25 , PWM_CHAN = 1
[PWM] PWM enabled, slice =  4 , _frequency =  1000.00
=============================================================
Change PWM DutyCycle to 50.00
[PWM] _PWM_config.top = 6649 , _actualFrequency = 2000.00
[PWM] Changing PWM frequency to 2000.00 and dutyCycle = 50.00
[PWM] pin =  25 , PWM_CHAN = 1
[PWM] PWM enabled, slice =  4 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
Change PWM DutyCycle to 10.00
[PWM] Changing PWM DutyCycle to 10.00 and keeping frequency = 2000.00
[PWM] pin =  25 , PWM_CHAN = 1
[PWM] PWM enabled, slice =  4 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
Change PWM DutyCycle to 50.00
[PWM] Changing PWM DutyCycle to 50.00 and keeping frequency = 2000.00
[PWM] pin =  25 , PWM_CHAN = 1
[PWM] PWM enabled, slice =  4 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
Change PWM DutyCycle to 10.00
[PWM] Changing PWM DutyCycle to 10.00 and keeping frequency = 2000.00
[PWM] pin =  25 , PWM_CHAN = 1
[PWM] PWM enabled, slice =  4 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
Change PWM DutyCycle to 50.00
[PWM] Changing PWM DutyCycle to 50.00 and keeping frequency = 2000.00
[PWM] pin =  25 , PWM_CHAN = 1
[PWM] PWM enabled, slice =  4 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
Change PWM DutyCycle to 10.00
[PWM] Changing PWM DutyCycle to 10.00 and keeping frequency = 2000.00
[PWM] pin =  25 , PWM_CHAN = 1
[PWM] PWM enabled, slice =  4 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
Change PWM DutyCycle to 50.00
[PWM] Changing PWM DutyCycle to 50.00 and keeping frequency = 2000.00
[PWM] pin =  25 , PWM_CHAN = 1
[PWM] PWM enabled, slice =  4 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
Change PWM DutyCycle to 10.00
[PWM] Changing PWM DutyCycle to 10.00 and keeping frequency = 2000.00
[PWM] pin =  25 , PWM_CHAN = 1
[PWM] PWM enabled, slice =  4 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
```

---

### 5. PWM_MultiChannel on RASPBERRY_PI_PICO

The following is the sample terminal output when running example [**PWM_MultiChannel**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_MultiChannel) on **RASPBERRY_PI_PICO**, running [`Earle Philhower's arduino-pico core`](https://github.com/earlephilhower/arduino-pico), to demonstrate the ability to output for both channels of a PWM slice


```cpp
Starting PWM_MultiChannel on RASPBERRY_PI_PICO
RP2040_PWM v1.7.0
=============================================================
Index	Pin	PWM_freq	DutyCycle	Actual Freq
=============================================================
0	10	1000.00		10.00		1000.00
1	11	1000.00		50.00		1000.00
=============================================================
```

---

### 6. PWM_Waveform on RASPBERRY_PI_PICO

The following is the sample terminal output when running example [**PWM_Waveform**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Waveform) on **RASPBERRY_PI_PICO**, running [`Earle Philhower's arduino-pico core`](https://github.com/earlephilhower/arduino-pico), to demonstrate how to use new `setPWM_manual()` function in wafeform creation


```cpp
Starting PWM_Waveform on RASPBERRY_PI_PICO
RP2040_PWM v1.7.0
[PWM] _PWM_config.top = 12499 , _actualFrequency = 1000.00
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 0
=============================================================
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 0
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 50
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 100
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 200
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 300
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 400
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 500
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 600
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 700
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 800
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 900
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 1000
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 1000
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 900
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 800
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 700
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 600
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 500
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 400
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 300
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 200
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 100
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 50
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 0
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 0
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 50
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 100
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 200
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 300
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 400
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 500
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 600
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 700
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 800
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 900
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 1000
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 1000
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 900
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 800
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 700
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 600
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 500
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 400
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 300
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 200
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 100
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 50
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 0
[PWM] pin =  10 , PWM_CHAN = 0
...
```

---

### 7. PWM_Waveform_Fast on RASPBERRY_PI_PICO

The following is the sample terminal output when running example [**PWM_Waveform_Fast**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Waveform_Fast) on **RASPBERRY_PI_PICO**, running [`arduino-pico core`](https://github.com/earlephilhower/arduino-pico), to demonstrate how to use new `setPWM_manual()` function in wafeform creation


```cpp
Starting PWM_Waveform_Fast on RASPBERRY_PI_PICO
RP2040_PWM v1.7.0
[PWM] _PWM_config.top = 12499 , _actualFrequency = 1000.00
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 0
=============================================================
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 0
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 50
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 100
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 200
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 300
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 400
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 500
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 600
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 700
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 800
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 900
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 1000
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 1000
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 900
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 800
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 700
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 600
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 500
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 400
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 300
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 200
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 100
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 50
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 0
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 0
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 50
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 100
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 200
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 300
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 400
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 500
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 600
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 700
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 800
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 900
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 1000
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 1000
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 900
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 800
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 700
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 600
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 500
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 400
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 300
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 200
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 100
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 50
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 0
[PWM] pin =  10 , PWM_CHAN = 0
[PWM] PWM enabled, slice = 5 , top = 1000 , div = 10 , level = 0
...
```

---


### 8. PWM_manual on RASPBERRY_PI_PICO

The following is the sample terminal output when running example [**PWM_manual**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_manual) on **RASPBERRY_PI_PICO**, running [`arduino-pico core`](https://github.com/earlephilhower/arduino-pico), to demonstrate how to use new `setPWM_DCPercentage_manual()` function in wafeform creation


```cpp
Starting PWM_manual on RASPBERRY_PI_PICO
RP2040_PWM v1.7.0
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 0.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 5.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 10.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 15.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 20.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 25.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 30.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 35.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 40.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 45.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 50.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
...
```

---

### 9. PWM_SpeedTest on RASPBERRY_PI_PICO

The following is the sample terminal output when running example [**PWM_SpeedTest**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_SpeedTest) on **RASPBERRY_PI_PICO**, running [`arduino-pico core`](https://github.com/earlephilhower/arduino-pico), to demonstrate how to use new faster `setPWM_manual_Fast()` function in wafeform creation, The time is `1597ns` compared to `2889ns` when using `setPWM_manual()` function

```cpp
Starting PWM_SpeedTest on RASPBERRY_PI_PICO
RP2040_PWM v1.7.0
=================================================================================================
Actual data: pin = 10, PWM DutyCycle % = 0.00, PWMPeriod = 13299, PWM Freq (Hz) = 1000.0000
=================================================================================================
Average time of setPWM function
ns=1598
ns=1597
ns=1597
ns=1597
ns=1597
ns=1597
ns=1597
ns=1597
ns=1597
ns=1597
...
```

---

### 10. PWM_PushPull on RASPBERRY_PI_PICO

The following is the sample terminal output when running example [**PWM_PushPull**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull) on **RASPBERRY_PI_PICO**, running [`arduino-pico core`](https://github.com/earlephilhower/arduino-pico), to demo the new `PushPull` mode

```cpp
Starting PWM_PushPull on RASPBERRY_PI_PICO
RP2040_PWM v1.7.0
[PWM] _PWM_config.top = 6249 , _actualFrequency = 2000.00
[PWM] _PWM_config.top = 3124 , _actualFrequency = 2000.00
[PWM] Changing PWM frequency to 2000.00 and dutyCycle = 30.00
[PWM] pinA =  18 , pinB =  19 , PWM_CHAN = 0
[PWM] PWM enabled, slice =  1 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
[PWM] TOP = 3124 , DIV = 10 , CPU_freq = 125000000
```


---

### 11. PWM_PushPull_DynamicDC on RASPBERRY_PI_PICO

The following is the sample terminal output when running example [**PWM_PushPull_DynamicDC**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull_DynamicDC) on **RASPBERRY_PI_PICO**, running [`arduino-pico core`](https://github.com/earlephilhower/arduino-pico), to demo the new `PushPull` mode

```cpp
Starting PWM_PushPull_DynamicDC on RASPBERRY_PI_PICO
RP2040_PWM v1.7.0
[PWM] _PWM_config.top = 6249 , _actualFrequency = 2000.00
[PWM] _PWM_config.top = 3124 , _actualFrequency = 2000.00
[PWM] Changing PWM frequency to 2000.00 and dutyCycle = 0.00
[PWM] pinA =  18 , pinB =  19 , PWM_CHAN = 0
[PWM] PWM enabled, slice =  1 , _frequency =  2000.00
Change PWM DutyCycle to 50.00
[PWM] Changing PWM DutyCycle to 50.00 and keeping frequency = 2000.00
[PWM] pinA =  18 , pinB =  19 , PWM_CHAN = 0
[PWM] PWM enabled, slice =  1 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
[PWM] TOP = 3124 , DIV = 10 , CPU_freq = 125000000
Change PWM DutyCycle to 10.00
[PWM] Changing PWM DutyCycle to 10.00 and keeping frequency = 2000.00
[PWM] pinA =  18 , pinB =  19 , PWM_CHAN = 0
[PWM] PWM enabled, slice =  1 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
[PWM] TOP = 3124 , DIV = 10 , CPU_freq = 125000000
Change PWM DutyCycle to 50.00
[PWM] Changing PWM DutyCycle to 50.00 and keeping frequency = 2000.00
[PWM] pinA =  18 , pinB =  19 , PWM_CHAN = 0
[PWM] PWM enabled, slice =  1 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
[PWM] TOP = 3124 , DIV = 10 , CPU_freq = 125000000
...
```


---

### 12. PWM_PushPull_DynamicFreq on RASPBERRY_PI_PICO

The following is the sample terminal output when running example [**PWM_PushPull_DynamicFreq**](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull_DynamicFreq) on **RASPBERRY_PI_PICO**, running [`arduino-pico core`](https://github.com/earlephilhower/arduino-pico), to demo the new `PushPull` mode

```cpp
Starting PWM_PushPull_DynamicFreq on RASPBERRY_PI_PICO
RP2040_PWM v1.7.0
[PWM] _PWM_config.top = 6249 , _actualFrequency = 2000.00
[PWM] _PWM_config.top = 3124 , _actualFrequency = 2000.00
[PWM] Changing PWM frequency to 2000.00 and dutyCycle = 0.00
[PWM] pinA =  18 , pinB =  19 , PWM_CHAN = 0
[PWM] PWM enabled, slice =  1 , _frequency =  2000.00
Change PWM Freq to 2000.00
[PWM] Changing PWM DutyCycle to 30.00 and keeping frequency = 2000.00
[PWM] pinA =  18 , pinB =  19 , PWM_CHAN = 0
[PWM] PWM enabled, slice =  1 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
[PWM] TOP = 3124 , DIV = 10 , CPU_freq = 125000000
Change PWM Freq to 1000.00
[PWM] _PWM_config.top = 6249 , _actualFrequency = 1000.00
[PWM] Changing PWM frequency to 1000.00 and dutyCycle = 30.00
[PWM] pinA =  18 , pinB =  19 , PWM_CHAN = 0
[PWM] PWM enabled, slice =  1 , _frequency =  1000.00
Actual PWM Frequency = 1000.00
[PWM] TOP = 6249 , DIV = 10 , CPU_freq = 125000000
Change PWM Freq to 2000.00
[PWM] _PWM_config.top = 3124 , _actualFrequency = 2000.00
[PWM] Changing PWM frequency to 2000.00 and dutyCycle = 30.00
[PWM] pinA =  18 , pinB =  19 , PWM_CHAN = 0
[PWM] PWM enabled, slice =  1 , _frequency =  2000.00
Actual PWM Frequency = 2000.00
[PWM] TOP = 3124 , DIV = 10 , CPU_freq = 125000000
Change PWM Freq to 1000.00
[PWM] _PWM_config.top = 6249 , _actualFrequency = 1000.00
[PWM] Changing PWM frequency to 1000.00 and dutyCycle = 30.00
[PWM] pinA =  18 , pinB =  19 , PWM_CHAN = 0
[PWM] PWM enabled, slice =  1 , _frequency =  1000.00
Actual PWM Frequency = 1000.00
[PWM] TOP = 6249 , DIV = 10 , CPU_freq = 125000000
...
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
 4. Permit PWM output for both channels of PWM slice.
 5. Use float `instead` of `double` for frequency and duty-cycle
 6. Add example [PWM_MultiChannel](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_MultiChannel) to demonstrate how to use both channels of PWM slice.
 7. Add efficient `setPWM_manual()` function to use in wafeform creation using PWM
 8. Add example [PWM_Waveform](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Waveform) to demonstrate how to use new `setPWM_manual()` function in wafeform creation
 9. Optimize library code and examples by using **reference-passing instead of value-passing** and **inline**
10. Add `setPWM_manual(pin, level)` function for efficiency in wafeform creation using PWM
11. Add example [PWM_Waveform_Fast](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Waveform_Fast) to demonstrate how to use new `setPWM_manual(pin, level)` function
12. Add `setPWM_Int()` function for optional `uint32_t dutycycle = real_dutycycle * 1000`
13. Add example [PWM_DynamicDutyCycle_Int](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_DynamicDutyCycle_Int) to demonstrate how to use new `setPWM_Int()` function
14. Add `minimal` example [PWM_Basic](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Basic)
15. Fix glitch when dynamically changing dutycycle. Check [Changing Duty Cycle Dynamically Creates Runt PWM pulse #10](https://github.com/khoih-prog/RP2040_PWM/issues/10)
16. Adjust `MIN_PWM_FREQUENCY` and `MAX_PWM_FREQUENCY` dynamically according to actual `F_CPU`
17. Add example [PWM_StepperControl](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_StepperControl) to demo how to control Stepper Motor using PWM
18. Add example [PWM_manual](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_manual) to demo how to correctly use PWM to generate waveform
19. Add function `setPWM_DCPercentage_manual()` to facilitate the setting PWM DC manually by using `DCPercentage`, instead of `absolute DCValue` depending on varying `TOP`
20. Add functions `getPin()` and `getActualDutyCycle()`
21. Optimize speed with new `setPWM_manual_Fast` function to improve almost 50% compared to `setPWM_manual`. Check 
22. Add example [PWM_SpeedTest](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_SpeedTest) to demo the better speed of new `setPWM_manual_Fast` function
23. Add functions `setPWMPushPull_Int`, `setPWMPushPull` and `setPWMPushPull_Period` for the new `PushPull` mode
24. Add these examples to demo the new `PushPull` mode
  - [PWM_PushPull](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull)
  - [PWM_PushPull_DynamicDC](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull_DynamicDC)
  - [PWM_PushPull_DynamicFreq](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_PushPull_DynamicFreq)
25. Fix bug of half frequency when using `phaseCorrect` mode
26. Improve `README.md` so that links can be used in other sites, such as `PIO`



---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Thanks to [americodias](https://github.com/americodias) to report bugs in 
- [Wrong frequency #1](https://github.com/khoih-prog/RP2040_PWM/issues/1) leading to v1.0.1
- [Change the PWM frequency #2](https://github.com/khoih-prog/RP2040_PWM/issues/2) leading to v1.0.2
2. Thanks to [Austin K. Litman](https://github.com/AKLitman) to report bugs in 
- [Attempting to Alter the Duty Cycle w/o changing any other values #3](https://github.com/khoih-prog/RP2040_PWM/issues/3) leading to v1.0.5
- [Request for Clarification on PWM Slices and A/B sides #5](https://github.com/khoih-prog/RP2040_PWM/issues/5) leading to v1.1.0
3. Thanks to [Joerg Starkmuth](https://github.com/Laserjones) to propose enhancement in 
- [Duty cycle as integer rather than float #6](https://github.com/khoih-prog/RP2040_PWM/issues/6) leading to v1.2.0 and v1.3.0
4. Thanks to [Dr. Benjamin Bird](https://github.com/Chick92) to make PR
- [added minimal viable program to get the user up and running #9](https://github.com/khoih-prog/RP2040_PWM/pull/9) leading to v1.3.1
5. Thanks to [Rocking Y Productions](https://github.com/RockingYProductions) to request enhancement in [Changing Duty Cycle Dynamically Creates Runt PWM pulse #10](https://github.com/khoih-prog/RP2040_PWM/issues/10), leading to v1.4.0
6. Thanks to [Paul van Dinther](https://github.com/dinther) for proposing new way to use PWM to drive `Stepper-Motor` in [Using PWM to step a stepper driver #16](https://github.com/khoih-prog/RP2040_PWM/issues/16), leading to v1.4.1
7. Thanks to [jmdodd95682](https://github.com/jmdodd95682) for open discussion about `setPWM_manual()` speed in [setPWM latency #19](https://github.com/khoih-prog/RP2040_PWM/issues/19), leading to v1.6.0
8. Thanks to [tinkerbug](https://github.com/tinkerbug) for open discussion about `pwm_set_output_polarity()` function in [pwm_set_output_polarity #21](https://github.com/khoih-prog/RP2040_PWM/discussions/21), leading to v1.7.0


<table>
  <tr>
    <td align="center"><a href="https://github.com/americodias"><img src="https://github.com/americodias.png" width="100px;" alt="americodias"/><br /><sub><b>⭐️ Américo Dias</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/AKLitman"><img src="https://github.com/AKLitman.png" width="100px;" alt="AKLitman"/><br /><sub><b>⭐️ Austin K. Litman</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/Laserjones"><img src="https://github.com/Laserjones.png" width="100px;" alt="Laserjones"/><br /><sub><b>⭐️ Joerg Starkmuth</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/Chick92"><img src="https://github.com/Chick92.png" width="100px;" alt="Chick92"/><br /><sub><b>⭐️ Dr. Benjamin Bird</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/RockingYProductions"><img src="https://github.com/RockingYProductions.png" width="100px;" alt="RockingYProductions"/><br /><sub><b>Rocking Y Productions</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/dinther"><img src="https://github.com/dinther.png" width="100px;" alt="dinther"/><br /><sub><b>Paul van Dinther</b></sub></a><br /></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/jmdodd95682"><img src="https://github.com/jmdodd95682.png" width="100px;" alt="jmdodd95682"/><br /><sub><b>jmdodd95682</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tinkerbug"><img src="https://github.com/tinkerbug.png" width="100px;" alt="tinkerbug"/><br /><sub><b>tinkerbug</b></sub></a><br /></td>
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


