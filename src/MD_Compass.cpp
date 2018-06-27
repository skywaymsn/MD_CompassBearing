
#include <Arduino.h>
#include <MD_Compass.h> // https://github.com/skywaymsn/MD_CompassBearing

namespace MD {

    Compass::Compass(int pin, unsigned long pulse_min, unsigned long pulse_max, targetBearing) {
        _currentBearing = _getCurrentBearing();
        _pulse_min = pulse_min;
        _pulse_max = pulse_max;
        pinMode(_pin, OUTPUT);
        _waypoint  = micros();
    }

    unsigned long Compass::_getCurrentBearing() {
        // Communicate with the compass
        if(_changed) {
            _changed = false;
            // map(value, from_low, from_high, to_low, to_high)
            _target_pulse_time = (unsigned long) map(_target_degrees, 0, _degrees_of_rotation, _pulse_min, _pulse_max);
        }
        return _target_pulse_time;
    }

}
