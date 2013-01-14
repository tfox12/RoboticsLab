#include "motor.h"
#include "vex_interface.h"

namespace RaspberryPi
{
    Motor::Motor(unsigned char p) : port(p), speed(0) { }

    void Motor::set_value(short value)
    {
        set_motor_value(port, value);
    }
}
