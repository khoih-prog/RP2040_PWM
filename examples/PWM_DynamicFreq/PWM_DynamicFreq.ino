/****************************************************************************************************************************
  PWM_DynamicFreq.ino
  For RP2040 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/RP2040_PWM
  Licensed under MIT license

  The RP2040 PWM block has 8 identical slices. Each slice can drive two PWM output signals, or measure the frequency
  or duty cycle of an input signal. This gives a total of up to 16 controllable PWM outputs. All 30 GPIO pins can be driven
  by the PWM block

  Version: 1.0.3

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K.Hoang      21/09/2021 Initial coding for RP2040 using ArduinoCore-mbed or arduino-pico core
  1.0.1   K.Hoang      24/09/2021 Fix bug generating wrong frequency
  1.0.2   K.Hoang      04/10/2021 Fix bug not changing frequency dynamically
  1.0.3   K.Hoang      05/10/2021 Not reprogram if same PWM frequency. Add PIO strict `lib_compat_mode`
*****************************************************************************************************************************/

#if ( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || \
      defined(ARDUINO_GENERIC_RP2040) ) && defined(ARDUINO_ARCH_MBED)

#warning USING_MBED_RP2040_PWM

#elif ( defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || \
        defined(ARDUINO_GENERIC_RP2040) ) && !defined(ARDUINO_ARCH_MBED)

#warning USING_MBED_RP2040_PWM
#else
#error This code is intended to run on the RP2040 mbed_nano, mbed_rp2040 or arduino-pico platform! Please check your Tools->Board setting.
#endif

#define _PWM_LOGLEVEL_        4

#include "RP2040_PWM.h"

#define LED_ON        LOW
#define LED_OFF       HIGH

#define pin0    16    // PWM channel 4B (D2)

RP2040_PWM* PWM_Instance;

double frequency;

char dashLine[] = "=============================================================";

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  delay(100);

  Serial.print(F("\nStarting PWM_DynamicFreq on ")); Serial.println(BOARD_NAME);
  Serial.println(RP2040_PWM_VERSION);

  frequency = 1000;
  PWM_Instance = new RP2040_PWM(pin0, frequency, 50);

  if (PWM_Instance)
  {
    PWM_Instance->setPWM();
  }

  Serial.println(dashLine);
}

void printPWMInfo(RP2040_PWM* PWM_Instance)
{
  uint32_t div = PWM_Instance->get_DIV();
  uint32_t top = PWM_Instance->get_TOP();

  Serial.print("Actual PWM Frequency = "); Serial.println(PWM_Instance->getActualFreq());

  PWM_LOGDEBUG5("TOP =", top, ", DIV =", div, ", CPU_freq =", PWM_Instance->get_freq_CPU());
}



void loop()
{
  delay(5000);
  frequency = 2000;
  Serial.print(F("Change PWM Freq to ")); Serial.println(frequency);
  PWM_Instance->setPWM(pin0, frequency, 50, true);

  printPWMInfo(PWM_Instance);

  delay(5000);
  frequency = 1000;
  Serial.print(F("Change PWM Freq to ")); Serial.println(frequency);
  PWM_Instance->setPWM(pin0, frequency, 50, true);
  printPWMInfo(PWM_Instance);
}