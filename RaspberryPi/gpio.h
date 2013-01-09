#ifndef _GPIO_H_
#define _GPIO_H_

namespace RaspberryPi
{
    enum alternate_function
    {
        input = 0,  // 000
        output = 1, // 001
        alt0 = 4,   // 100
        alt1 = 5,   // 101
        alt2 = 6,   // 110
        alt3 = 7,   // 111
        alt4 = 3,   // 011
        alt5 = 2    // 010
    };

    class Gpio
    {
    public:
        Gpio(unsigned char);
        void set_alternate_function(alternate_function);
        void set();
        void clear();
    private:
        unsigned char pin_number;
    };

    class GpioInterface
    {
        friend class Gpio;

        public:
            static GpioInterface * instance();
        private:
            GpioInterface();
            static GpioInterface * INSTANCE;
            static volatile unsigned * gpio_base;
    };
}

#endif
