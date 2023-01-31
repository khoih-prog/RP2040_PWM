/****************************************************************************************************************************
  PWM_PushPull.ino
  For RP2040 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/RP2040_PWM
  Licensed under MIT license

  The RP2040 PWM block has 8 identical slices. Each slice can drive two PWM output signals, or measure the frequency
  or duty cycle of an input signal. This gives a total of up to 16 controllable PWM outputs. All 30 GPIO pins can be driven
  by the PWM block
*****************************************************************************************************************************/

#define _PWM_LOGLEVEL_        4
#include "RP2040_PWM.h"

//creates pwm instance
RP2040_PWM* PWM_Instance;

float frequency = 2000.0f;
float dutyCycle = 30.0f;

// Pins have to be in pairs of the same PWM slice / channel
// Check https://github.com/khoih-prog/RP2040_PWM#programmers-model
// For example: pins 0/1, 2/3, 4/5, 6/7, 8/9, 10/11, 12/13, 14/15, 16/17, 18/19, 20/21, 22/23, 24/25, 26/27, 28/29

#define pinToUseA      18     // PWM1A
#define pinToUseB      19     // PWM1A

void printPWMInfo(RP2040_PWM* PWM_Instance)
{
  uint32_t div = PWM_Instance->get_DIV();
  uint32_t top = PWM_Instance->get_TOP();

  Serial.print("Actual PWM Frequency = ");
  Serial.println(PWM_Instance->getActualFreq());

  PWM_LOGDEBUG5("TOP =", top, ", DIV =", div, ", CPU_freq =", PWM_Instance->get_freq_CPU());
}

void setup()
{ 
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(100);

  Serial.print(F("\nStarting PWM_PushPull on "));
  Serial.println(BOARD_NAME);
  Serial.println(RP2040_PWM_VERSION);

  // Use just one of these 2 for a pair
  // assigns pinToUseA, with frequency of 200 Hz and a duty cycle of 0%
  PWM_Instance = new RP2040_PWM(pinToUseA, frequency, 0);
  // assigns pinToUseB, with frequency of 200 Hz and a duty cycle of 0%
  //PWM_Instance = new RP2040_PWM(pinToUseB, frequency, 0);

  // pinToUseA always with same polarity, pinToUseB with reversed polarity
  //PWM_Instance->setPWMPushPull(pinToUseA, pinToUseB, frequency, dutyCycle);
  // pinToUseA always with same polarity, pinToUseB shifted 180 deg
  PWM_Instance->setPWMPushPull(pinToUseA, pinToUseB, frequency, dutyCycle);

  printPWMInfo(PWM_Instance);
}

void loop()
{
}
