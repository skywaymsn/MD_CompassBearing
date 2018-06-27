#ifndef MD_COMPASS
#define MD_COMPASS

#include <Arduino.h>

namespace MD {
  class Compass {
    public:
      Compass(int pin, unsigned long pulse_min, unsigned long pulse_max); // pulse position modulation / pulse width modulation time in microseconds
      void currentBearing(unsigned long value); // 20ms default: length of delay between sending position pulses
      void targetBearing(unsigned long value);  // the hardware maximum value for rotational degrees
      void rotationLeftDistance(unsigned long value);              // Distance to turn left for the target bearing
      void rotationRightDistance(unsigned long value);              // Distance to turn right for the target bearing
    private:
        unsigned long _getCurrentBearing(); // Read the current bearing from the device
      int _pin;
      unsigned long _pulse_min;             // hardware required microsecond floor for the movement pulse with this servo
      unsigned long _pulse_max;             // hardware required microsecond ceiling for the movement ceiling with this servo
      unsigned long _waypoint;              // waypoint tracker for the pulse interval and pulse length timers
      unsigned long _interval  = 20000;     // 20 milliseconds displayed as microseconds, how long between movement pulses
      int _degrees_of_rotation = 180;       // total degrees of rotation for the servo [0 - 360]
      int _target_degrees      = 0;         // where the servo should be moving to or holding at
      bool _active             = false;     // stops the servo from moving on startup, before the first move command is received
      bool _changed            = false;     // flag to recalculate the position microseconds
      bool _pin_is_high        = false;     // holds the pin state so we only write HIGH or LOW once instead of on each loop
      unsigned long _target_pulse_time = 0; // memoized computation from degrees to microseconds
      unsigned long _targetPulseTime();     // return target microseconds based upon min, max, and target degrees
  };
}
#endif
