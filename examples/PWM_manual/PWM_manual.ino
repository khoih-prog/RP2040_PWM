/****************************************************************************************************************************
  PWM_manual.ino
  For RP2040 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/RP2040_PWM
  Licensed under MIT license

  The RP2040 PWM block has 8 identical slices. Each slice can drive two PWM output signals, or measure the frequency
  or duty cycle of an input signal. This gives a total of up to 16 controllable PWM outputs. All 30 GPIO pins can be driven
  by the PWM block
*****************************************************************************************************************************/
// This example to demo the new function setPWM_manual(uint8_t pin, uint16_t top, uint8_t div, uint16_t level, bool phaseCorrect = false)
// used to generate a waveform. Check https://github.com/khoih-prog/RP2040_PWM/issues/6

#define _PWM_LOGLEVEL_        2

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

#define UPDATE_INTERVAL       1000L

// Using setPWM_DCPercentage_manual if true
#define USING_DC_PERCENT      true

#define LED_ON        LOW
#define LED_OFF       HIGH

#define pinLed        25    // GP25, On-board BUILTIN_LED
#define pin0          16    // GP16, PWM channel 4B (D2)
#define pin10         10    // PWM channel 5A
#define pin11         11    // PWM channel 5B

#define pinToUse      pin10

RP2040_PWM* PWM_Instance;

float    frequency = 1000.0f;
//float    frequency = 10000.0f;

#if USING_DC_PERCENT
  float    dutycyclePercent = 0.0f;
  float    DCStepPercent    = 5.0f;
#else
  uint16_t dutycycle = 0;
  uint16_t DCStep;
#endif

uint16_t PWMPeriod;

char dashLine[] = "=================================================================================================";

void printPWMInfo(RP2040_PWM* PWM_Instance)
{
  Serial.println(dashLine);
  Serial.print("Actual data: pin = ");
  Serial.print(PWM_Instance->getPin());
  Serial.print(", PWM DutyCycle % = ");
  Serial.print(PWM_Instance->getActualDutyCycle() / 1000.0f);
  Serial.print(", PWMPeriod = ");
  Serial.print(PWM_Instance->get_TOP());
  Serial.print(", PWM Freq (Hz) = ");
  Serial.println(PWM_Instance->getActualFreq(), 4);
  Serial.println(dashLine);
}

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(100);

  Serial.print(F("\nStarting PWM_manual on "));
  Serial.println(BOARD_NAME);
  Serial.println(RP2040_PWM_VERSION);

  // Create a dummy instance
  PWM_Instance = new RP2040_PWM(pinToUse, frequency, 0);

  if (PWM_Instance)
  {
    uint16_t PWM_TOP   = PWM_Instance->get_TOP();
    uint16_t PWM_DIV   = PWM_Instance->get_DIV();
    uint16_t PWM_Level = 0;

    // setPWM_manual(uint8_t pin, uint16_t top, uint8_t div, uint16_t level, bool phaseCorrect = false)
    PWM_Instance->setPWM_manual(pinToUse, PWM_TOP, PWM_DIV, PWM_Level, true);
    
    PWMPeriod = PWM_Instance->get_TOP();

#if !USING_DC_PERCENT    
    // 5% steps
    DCStep = round(PWMPeriod / 20.0f);
#endif
  }
}

void loop()
{
  static unsigned long update_timeout = UPDATE_INTERVAL;

  // Update DC every UPDATE_INTERVAL (100) milliseconds
  if (millis() > update_timeout)
  {
#if USING_DC_PERCENT
    PWM_Instance->setPWM_DCPercentage_manual(pinToUse, dutycyclePercent);

    dutycyclePercent += DCStepPercent;

    if (dutycyclePercent > 100.0f)
      dutycyclePercent = 0.0f;
#else
    if (dutycycle > PWMPeriod)
    {
      PWM_Instance->setPWM_manual(pinToUse, PWMPeriod);
      dutycycle = 0;
    }
    else
    {
      PWM_Instance->setPWM_manual(pinToUse, dutycycle);
      dutycycle += DCStep;
    }
#endif

    printPWMInfo(PWM_Instance);
    
    update_timeout = millis() + UPDATE_INTERVAL;
  }
}
