/****************************************************************************************************************************
  PWM_DynamicDutyCycle_Int.ino
  For RP2040 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/RP2040_PWM
  Licensed under MIT license

  The RP2040 PWM block has 8 identical slices. Each slice can drive two PWM output signals, or measure the frequency
  or duty cycle of an input signal. This gives a total of up to 16 controllable PWM outputs. All 30 GPIO pins can be driven
  by the PWM block
*****************************************************************************************************************************/

#define _PWM_LOGLEVEL_        1

#if ( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || \
      defined(ARDUINO_GENERIC_RP2040) ) && defined(ARDUINO_ARCH_MBED)

#if(_PWM_LOGLEVEL_>3)
  #warning USING_MBED_RP2040_PWM
#endif

#elif ( defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || \
        defined(ARDUINO_GENERIC_RP2040) ) && !defined(ARDUINO_ARCH_MBED)

#if(_PWM_LOGLEVEL_>3)
  #warning USING_RP2040_PWM
#endif
#else
#error This code is intended to run on the RP2040 mbed_nano, mbed_rp2040 or arduino-pico platform! Please check your Tools->Board setting.
#endif

#include "RP2040_PWM.h"

#define LED_ON        LOW
#define LED_OFF       HIGH

#define pinLed        25    // GP25, On-board BUILTIN_LED
#define pin0          16    // GP16, PWM channel 4B (D2)
#define pin10         10    // PWM channel 5A
#define pin11         11    // PWM channel 5B

#define pinToUse      pin10

RP2040_PWM* PWM_Instance;

float frequency;
uint32_t dutyCycle;

char dashLine[] = "=============================================================";

void setup()
{
  Serial.begin(115200);

  while (!Serial);

  delay(100);

  Serial.print(F("\nStarting PWM_DynamicDutyCycle_Int on "));
  Serial.println(BOARD_NAME);
  Serial.println(RP2040_PWM_VERSION);

  frequency = 1000;

  PWM_Instance = new RP2040_PWM(pinToUse, frequency, 50);

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

  Serial.print("Actual PWM Frequency = ");
  Serial.println(PWM_Instance->getActualFreq());

  PWM_LOGDEBUG5("TOP =", top, ", DIV =", div, ", CPU_freq =", PWM_Instance->get_freq_CPU());
}

void loop()
{
  delay(5000);

  frequency = 5000;

  // dutyCycle = real_dutyCycle * 1000
  dutyCycle = 50000;

  Serial.print(F("Change PWM DutyCycle to "));
  Serial.println((float) dutyCycle / 1000);
  PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);

  printPWMInfo(PWM_Instance);

  delay(5000);

  // dutyCycle = real_dutyCycle * 1000
  dutyCycle = 20000;

  Serial.print(F("Change PWM DutyCycle to "));
  Serial.println((float) dutyCycle / 1000);
  PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
  printPWMInfo(PWM_Instance);
}
