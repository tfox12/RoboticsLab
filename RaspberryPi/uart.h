#ifndef _UART_H_
#define _UART_H_

namespace RaspberryPi
{
    class Uart
    {
    public:

        Uart();
        void put(unsigned char);
        unsigned char get();

    private:

        static volatile unsigned * uart_base;
        static volatile unsigned * setup_uart_pointer();

        void setup_uart_gpio();
        void setup_uart_registers();
        
    };
}

#endif
