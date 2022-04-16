# RP2040_PWM Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/RP2040_PWM.svg?)](https://www.ardu-badge.com/RP2040_PWM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/RP2040_PWM.svg)](https://github.com/khoih-prog/RP2040_PWM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/RP2040_PWM/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/RP2040_PWM.svg)](http://github.com/khoih-prog/RP2040_PWM/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.2.0](#Releases-v120)
  * [Releases v1.1.1](#Releases-v111)
  * [Releases v1.1.0](#Releases-v110)
  * [Releases v1.0.5](#Releases-v105)
  * [Releases v1.0.4](#Releases-v104)
  * [Releases v1.0.3](#Releases-v103)
  * [Releases v1.0.2](#Releases-v102)
  * [Releases v1.0.1](#Releases-v101)
  * [Initial Releases v1.0.0](#Initial-Releases-v100)

---
---

## Changelog

### Releases v1.2.0

1. Add efficient `setPWM_manual()` function to use in wafeform creation using PWM. Check [Duty cycle as integer rather than float #6](https://github.com/khoih-prog/RP2040_PWM/issues/6)
2. Add example [PWM_Waveform](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_Waveform) to demonstrate how to use new `setPWM_manual()` function in wafeform creation
3. Optimize library code and examples by using **reference-passing instead of value-passing**.

### Releases v1.1.1

1. Fix compiler warnings.
2. Display informational warning when `_PWM_LOGLEVEL_` > 3

### Releases v1.1.0

1. Permit PWM output for both channels of PWM slice. Check [Request for Clarification on PWM Slices and A/B sides #5](https://github.com/khoih-prog/RP2040_PWM/issues/5)
2. Use float `instead` of `double` for frequency and duty-cycle
3. Add example [PWM_MultiChannel](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_MultiChannel) to demonstrate how to use both channels of PWM slice.


### Releases v1.0.5

1. Permit changing dutyCycle and keep same frequency on-the-fly. Check [Attempting to Alter the Duty Cycle w/o changing any other values #3](https://github.com/khoih-prog/RP2040_PWM/issues/3)
2. Add example [PWM_DynamicDutyCycle](https://github.com/khoih-prog/RP2040_PWM/tree/main/examples/PWM_DynamicDutyCycle) to demonstrate new feature
3. Add support for more boards using arduino-pico core, such as ADAFRUIT_ITSYBITSY_RP2040, CYTRON_MAKER_NANO_RP2040, SPARKFUN_PROMICRO_RP2040, CHALLENGER_2040_WIFI_RP2040, ILABS_2040_RPICO32_RP2040, MELOPERO_SHAKE_RP2040, SOLDERPARTY_RP2040_STAMP, UPESY_RP2040_DEVKIT, WIZNET_5100S_EVB_PICO, etc.
4. Display compiler informational warning messages only when `_PWM_LOGLEVEL_` > 3


### Releases v1.0.4

1. Fix platform in `library.json`

### Releases v1.0.3

1. Not reprogram if same PWM frequency. 
2. Add PIO strict `lib_compat_mode`


### Releases v1.0.2

1. Fix bug not changing frequency dynamically. See [Change the PWM frequency #2](https://github.com/khoih-prog/RP2040_PWM/issues/2)

### Releases v1.0.1

1. Fix bug generating wrong frequency. See [Wrong frequency #1](https://github.com/khoih-prog/RP2040_PWM/issues/1)


### Initial Releases v1.0.0

1. Initial coding to support **RP2040-based boards** such as Nano_RP2040_Connect, RASPBERRY_PI_PICO, etc. using either RP2040 [**ArduinoCore-mbed mbed_nano or mbed_rp2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico core**](https://github.com/earlephilhower/arduino-pico)
2. The purely hardware-based PWM channel can generate from very low (lowest is 7.5Hz) to very high PWM frequencies (in the **MHz** range, up to **62.5MHz**).

