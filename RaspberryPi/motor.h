#ifndef _MOTOR_H_
#define _MOTOR_H_

namespace RaspberryPi
{
    class Motor
    {
    public:

        Motor(unsigned char);
        void set_value(short);
    
    private:

        unsigned char port;
        char speed;
    };
}

#endif
