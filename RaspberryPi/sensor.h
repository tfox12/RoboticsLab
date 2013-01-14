#ifndef _SENSOR_H_
#define _SENSOR_H_

namespace RaspberryPi
{
    class Sensor
    {
    public:

        Sensor(unsigned char);
        short get_value();

    private:

        unsigned char port;
    };
}

#endif
