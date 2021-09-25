/****************************************************************************************************************************
  RP2040_PWM.h
  For RP2040 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/RP2040_PWM
  Licensed under MIT license

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one RP2040 STM32 timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.

  Version: 1.0.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K.Hoang      21/09/2021 Initial coding for RP2040 using ArduinoCore-mbed or arduino-pico core
  1.0.1   K.Hoang      24/09/2021 Fix bug generating wrong frequency
*****************************************************************************************************************************/

#pragma once

#ifndef RP2040_PWM_H
#define RP2040_PWM_H

#if ( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || \
      defined(ARDUINO_GENERIC_RP2040) ) && defined(ARDUINO_ARCH_MBED)
  #if defined(USING_MBED_RP2040_PWM)
    #undef USING_MBED_RP2040_PWM
  #endif  
  #define USING_MBED_RP2040_PWM       true
  
  #warning USING_MBED_RP2040_PWM in RP2040_PWM.h
  
#elif ( defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) ||  \
        defined(ARDUINO_GENERIC_RP2040) ) && !defined(ARDUINO_ARCH_MBED) 
  #if defined(USING_RP2040_PWM)
    #undef USING_RP2040_PWM
  #endif  
  #define USING_RP2040_PWM            true
  
  #warning USING_MBED_RP2040_PWM in RP2040_PWM.h
#else
  #error This code is intended to run on the RP2040 mbed_nano, mbed_rp2040 or arduino-pico platform! Please check your Tools->Board setting.
#endif


#ifndef RP2040_PWM_VERSION
  #define RP2040_PWM_VERSION       "RP2040_PWM v1.0.1"
#endif

#include <math.h>
#include <float.h>
#include "hardware/pwm.h"

#include "PWM_Generic_Debug.h"

#define MAX_PWM_FREQUENCY        (62500000.0f)
#define MIN_PWM_FREQUENCY        (7.5f)

///////////////////////////////////////////////////////////////////

class RP2040_PWM
{ 
  public:
  
  RP2040_PWM(uint8_t pin, double frequency, double dutycycle, bool phaseCorrect = false)
  {
#if defined(F_CPU)
    freq_CPU = F_CPU;
#else
    freq_CPU = 125000000;
#endif

    _pin          = pin;
    _frequency    = frequency;
    _dutycycle    = dutycycle;
    
    _phaseCorrect = phaseCorrect;
  
    if (!calc_TOP_and_DIV(frequency))
    {
      _frequency  = 0;
    }
          
    _pin          = pin;
    _frequency    = frequency;
    _dutycycle    = dutycycle;
    
    _phaseCorrect = phaseCorrect;
  }
  
  ///////////////////////////////////////////
  
  ~RP2040_PWM();
  
  ///////////////////////////////////////////
  
  bool setPWM()
  {
    return setPWM(_pin, _frequency, _dutycycle, _phaseCorrect);
  }
  
  ///////////////////////////////////////////
  
  bool setPWM(uint8_t pin, double frequency, double dutycycle, bool phaseCorrect = false)
  {
    if ( (frequency <= MAX_PWM_FREQUENCY) && (frequency >= MIN_PWM_FREQUENCY) )
    {   
      _pin        = pin;
      _frequency  = frequency;
      _dutycycle  = dutycycle;
      
      gpio_set_function(_pin, GPIO_FUNC_PWM);
      
      _slice_num = pwm_gpio_to_slice_num(_pin);
      
      pwm_config config = pwm_get_default_config();
      
      // Set phaseCorrect
      pwm_set_phase_correct(_slice_num, phaseCorrect);
         
      pwm_config_set_clkdiv_int(&config, _PWM_config.div);
      pwm_config_set_wrap(&config, _PWM_config.top);
      
      // auto start running once configured
      pwm_init(_slice_num, &config, true);
      pwm_set_gpio_level(_pin, ( _PWM_config.top * _dutycycle ) / 100 );
      
      _enabled = true;
    
      return true;
    }
    else
      return false;
  }
  
  ///////////////////////////////////////////

  bool setPWM_Period(uint8_t pin, double period_us, double dutycycle, bool phaseCorrect = false)
  {
    return setPWM(pin, 1000000.0f / period_us, dutycycle, phaseCorrect);
  }
  
  ///////////////////////////////////////////
  
  void enablePWM()
  {
    pwm_set_enabled(_slice_num, true);
    _enabled = true;
  }
  
  ///////////////////////////////////////////
  
  void disablePWM()
  {
    pwm_set_enabled(_slice_num, false);
    _enabled = false;
  }
  
  ///////////////////////////////////////////
  
  uint32_t get_TOP()
  {
    return _PWM_config.top;
  }
  
  ///////////////////////////////////////////
  
  uint32_t get_DIV()
  {
    return _PWM_config.div;
  }
  
  ///////////////////////////////////////////
  
  double getActualFreq()
  {
    return _actualFrequency;
  }
  
  ///////////////////////////////////////////
  
  uint32_t get_freq_CPU()
  {
    return freq_CPU;
  }
  
  ///////////////////////////////////////////////////////////////////
  
  private:
  
  uint32_t    freq_CPU;
  uint8_t     _pin;
  uint8_t     _slice_num;
  pwm_config  _PWM_config;
  
  double      _actualFrequency;
  double      _frequency;
  double      _dutycycle;
  bool        _phaseCorrect;
  
  bool        _enabled;
  
  ///////////////////////////////////////////
  
  // https://datasheets.raspberrypi.org/rp2040/rp2040-datasheet.pdf, page 549
  // https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__pwm.html
  
  ///////////////////////////////////////////
  
  bool calc_TOP_and_DIV(double freq)
  {           
    if (freq >= 2000.0)
    {
      _PWM_config.div = 1;
    }
    else if (freq >= 200.0) 
    {
      _PWM_config.div = 10;
    }
    else if (freq >= 20.0) 
    {
      _PWM_config.div = 100;
    }
    else if (freq >= 10.0) 
    {
      _PWM_config.div = 200;
    }
    else if (freq >= MIN_PWM_FREQUENCY)
    {
      _PWM_config.div = 255;
    }
    else
    {
      PWM_LOGERROR1("Error, freq must be >= ", MIN_PWM_FREQUENCY);
      
      return false;
    }
    
    // Formula => PWM_Freq = ( F_CPU ) / [ ( TOP + 1 ) * ( DIV + DIV_FRAC/16) ]
    _PWM_config.top = ( freq_CPU / freq / _PWM_config.div ) - 1;
    
    _actualFrequency = ( freq_CPU  ) / ( (_PWM_config.top + 1) * _PWM_config.div );
    
    PWM_LOGDEBUG3("_PWM_config.top =", _PWM_config.top, ", _actualFrequency =", _actualFrequency);
    
    return true; 
  }
};

///////////////////////////////////////////


#endif    // RP2040_PWM_H

