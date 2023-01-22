/****************************************************************************************************************************
  PWM_Multi.ino
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

#define pin0    25    // PWM channel 4B, BUILTIN_LED
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

float dutyCycle[NUM_OF_PINS]  = { 10.0f, 50.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f };

float freq[] = { 20.0f, 30.0f, 40.0f, 1000.0f, 2000.0f, 3000.0f, 8000.0f, 9999.0f };


RP2040_PWM* PWM_Instance[NUM_OF_PINS];

char dashLine[] = "=============================================================";

void setup()
{
  Serial.begin(115200);

  while (!Serial);

  delay(100);

  Serial.print(F("\nStarting PWM_Multi on "));
  Serial.println(BOARD_NAME);
  Serial.println(RP2040_PWM_VERSION);

  Serial.println(dashLine);
  Serial.println("Index\tPin\tPWM_freq\tDutyCycle\tActual Freq");
  Serial.println(dashLine);

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    Serial.print(index);
    Serial.print("\t");
    Serial.print(PWM_Pins[index]);
    Serial.print("\t");
    Serial.print(freq[index]);
    Serial.print("\t\t");
    Serial.print(dutyCycle[index]);

    PWM_Instance[index] = new RP2040_PWM(PWM_Pins[index], freq[index], dutyCycle[index]);

    if (PWM_Instance[index])
    {
      PWM_Instance[index]->setPWM();

      uint32_t div = PWM_Instance[index]->get_DIV();
      uint32_t top = PWM_Instance[index]->get_TOP();

      Serial.print("\t\t");
      Serial.println(PWM_Instance[index]->getActualFreq());

      PWM_LOGDEBUG5("TOP =", top, ", DIV =", div, ", CPU_freq =", PWM_Instance[index]->get_freq_CPU());
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
