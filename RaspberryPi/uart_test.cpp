#include "uart.h"
#include <iostream>

int main()
{
    RaspberryPi::Uart u;

    std::cout << "COMMAND ME!" << std::endl;
    while(true)
    {
        char c;
        std::cin >> c;

        if(c=='w')
        {
            u.put(0);
        }
        else if(c=='s')
        {
            u.put(1);
        }
        else if(c=='a')
        {
            u.put(2);
        }
        else if(c=='d')
        {
            u.put(3);
        }
    }
}
