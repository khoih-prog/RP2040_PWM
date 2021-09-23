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

  Version: 1.0.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K.Hoang      21/09/2021 Initial coding for RP2040 using ArduinoCore-mbed or arduino-pico core
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
  #define RP2040_PWM_VERSION       "RP2040_PWM v1.0.0"
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
  //
  // Best-fit algorithm from https://www.raspberrypi.org/forums/viewtopic.php?f=144&t=317593
  
  bool calc_TOP_and_DIV_HighFreq(double freq)
  {
    #define BIG_FLOAT                     2000000000.0f
    #define MAX_16_BIT                    65536
    #define MAX_12_BIT                    4096
  
    unsigned int Top_p_1;                 // Top + 1
    double PWM_Freq = freq;               // frequency required
    double bestfit_PWM_Freq;              // closest frequency
    double PWM_Freq_diff;                 // frequency error in Hz
    double PWM_Freq_bestdiff;             // best absolute error in Hz
    unsigned int best_TOP_P_1 = 1;        // best Top + 1
    double best_DIV_x_16 = 0;             // best DIV * 16

    // Will use 16X vdiv so loop counters are integer
    // to equal this out main clock is also X16
    unsigned int vsDiv;

    // used to check error is not increasing as DIV increases
    // so I can escape the DIV loop/
    double vLastError;

    // initialise current error by maxing out
    PWM_Freq_bestdiff = DBL_MAX;
   
    Top_p_1 = min(MAX_16_BIT, (freq_CPU / PWM_Freq) + 2) ;

    while (Top_p_1 > 1)
    {
      // max out last error
      vLastError = DBL_MAX;
     
      vsDiv = max(16, ((int)(BIG_FLOAT / PWM_Freq / Top_p_1)) - 2);

      while (vsDiv < MAX_12_BIT)
      {
        bestfit_PWM_Freq = BIG_FLOAT / (vsDiv * Top_p_1);
        PWM_Freq_diff = fabs(bestfit_PWM_Freq - PWM_Freq);

        // bomb out DIV loop if error rising
        if (PWM_Freq_diff > vLastError)
          break;

        vLastError = PWM_Freq_diff ;

        if (PWM_Freq_diff < PWM_Freq_bestdiff)
        {
          PWM_LOGDEBUG7("bestfit_PWM_Freq = ", bestfit_PWM_Freq, ", PWM_Freq_diff = ", PWM_Freq_diff, ", Top_p_1 - 1 = ", 
                          Top_p_1 - 1, ", vsDiv/16.0 = ", vsDiv / 16.0);
          
          PWM_Freq_bestdiff = PWM_Freq_diff;
          best_TOP_P_1      = Top_p_1;
          best_DIV_x_16   = vsDiv;
        }

        vsDiv += 1;
      }

      Top_p_1 -= 1;
    }
    
    bestfit_PWM_Freq = freq_CPU / (best_DIV_x_16 * best_TOP_P_1 / 16.0);
    PWM_Freq_diff = fabs(bestfit_PWM_Freq - PWM_Freq);

    _PWM_config.div = best_DIV_x_16 / 16;
    _PWM_config.top = best_TOP_P_1 - 1;

    _actualFrequency = bestfit_PWM_Freq;

    PWM_LOGINFO5("PWM_Freq = ", freq, ", _actualFrequency = ", _actualFrequency, ", PWM_Freq_diff = ", PWM_Freq_diff);
    PWM_LOGDEBUG3("TOP = ", _PWM_config.div, "DIV = ", _PWM_config.div);

    return true;
  }
  
  ///////////////////////////////////////////
  
  bool calc_TOP_and_DIV(double freq)
  {           
    if (freq >= 2000.0)
    {
      calc_TOP_and_DIV_HighFreq(freq);
      return true;
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
      calc_TOP_and_DIV_HighFreq(freq);
      return true;
    }
    else
    {
      PWM_LOGERROR1("Error, freq must be >= ", MIN_PWM_FREQUENCY);
      
      return false;
    }
    
    // Formula => PWF_Freq = ( F_CPU ) / [ ( TOP + 1 ) * ( DIV + DIV_FRAC/16) ]
    _PWM_config.top = ( freq_CPU / freq / _PWM_config.div ) - 1;
    
    _actualFrequency = ( freq_CPU  ) / ( (_PWM_config.top + 1) * _PWM_config.div );
    
    PWM_LOGDEBUG3("_PWM_config.top =", _PWM_config.top, ", _actualFrequency =", _actualFrequency);
    
    return true; 
  }
};

///////////////////////////////////////////


#endif    // RP2040_PWM_H

