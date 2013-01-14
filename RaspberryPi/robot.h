#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "motor.h"
#include "sensor.h"

#include <string>

namespace RaspberryPi
{
    class Robot
    {
    public:
        
        Robot();

    protected:
        
        Motor motors[8];
        Sensor digital[12];
        Sensor analog[8];
    };
}

#endif
