/****************************************************************************************************************************
  PWM_Waveform_Fast.ino
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

#define LED_ON        LOW
#define LED_OFF       HIGH

#define pinLed        25    // GP25, On-board BUILTIN_LED
#define pin0          16    // GP16, PWM channel 4B (D2)
#define pin10         10    // PWM channel 5A
#define pin11         11    // PWM channel 5B

#define pinToUse      pin10

RP2040_PWM* PWM_Instance;

typedef struct
{
  uint16_t top;
  uint8_t div;
  uint16_t level;
} PWD_Data;

#define NUM_PWM_POINTS      24

// PWM Freq = 12487 Hz
PWD_Data PWM_data[NUM_PWM_POINTS] =
{
  {  1000, 10,    0 },
  {  1000, 10,   50 },
  {  1000, 10,  100 },
  {  1000, 10,  200 },
  {  1000, 10,  300 },
  {  1000, 10,  400 },
  {  1000, 10,  500 },
  {  1000, 10,  600 },
  {  1000, 10,  700 },
  {  1000, 10,  800 },
  {  1000, 10,  900 },
  {  1000, 10, 1000 },
  {  1000, 10, 1000 },
  {  1000, 10,  900 },
  {  1000, 10,  800 },
  {  1000, 10,  700 },
  {  1000, 10,  600 },
  {  1000, 10,  500 },
  {  1000, 10,  400 },
  {  1000, 10,  300 },
  {  1000, 10,  200 },
  {  1000, 10,  100 },
  {  1000, 10,   50 },
  {  1000, 10,    0 },
};

float frequency;

// You can select any value
PWD_Data PWM_data_idle = PWM_data[0];

char dashLine[] = "=============================================================";

void setup()
{
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(100);

  Serial.print(F("\nStarting PWM_Waveform_Fast on "));
  Serial.println(BOARD_NAME);
  Serial.println(RP2040_PWM_VERSION);

  frequency = 1000;

  // Create a dummy instance
  PWM_Instance = new RP2040_PWM(pinToUse, frequency, 0);

  if (PWM_Instance)
  {
    // setPWM_manual(uint8_t pin, uint16_t top, uint8_t div, uint16_t level, bool phaseCorrect = false)
    PWM_Instance->setPWM_manual(pinToUse, PWM_data_idle.top, PWM_data_idle.div, PWM_data_idle.level, true);
  }

  Serial.println(dashLine);
}

void printPWMInfo(RP2040_PWM* PWM_Instance)
{
  uint32_t div = PWM_Instance->get_DIV();
  uint32_t top = PWM_Instance->get_TOP();

  // PWM_Freq = ( F_CPU ) / [ ( TOP + 1 ) * ( DIV + DIV_FRAC/16) ]
  PWM_LOGINFO1("Actual PWM Frequency = ",
               PWM_Instance->get_freq_CPU() / ( (PWM_Instance->get_TOP() + 1) * (PWM_Instance->get_DIV() ) ) );

  PWM_LOGDEBUG5("TOP =", top, ", DIV =", div, ", CPU_freq =", PWM_Instance->get_freq_CPU());
}

void loop()
{
  for (int index = 0; index < NUM_PWM_POINTS; index++)
  {
    PWM_Instance->setPWM_manual(pinToUse, PWM_data[index].level);

    // Use at low freq to check
    //printPWMInfo(PWM_Instance);

    // delay something here between data
    delay(100);
  }
}
