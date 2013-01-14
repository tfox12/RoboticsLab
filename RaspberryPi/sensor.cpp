#include "sensor.h"
#include "vex_interface.h"

namespace RaspberryPi
{
    Sensor::Sensor(unsigned char p) : port(p) { }
    
    short Sensor::get_value()
    {
        return get_sensor_value(port);
    }
}
