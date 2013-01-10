#include "uart.h"
#include "gpio.h"
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/mman.h>
#include <fcntl.h>

namespace RaspberryPi
{
    volatile unsigned * Uart::uart_base = Uart::setup_uart_pointer();

    volatile unsigned * Uart::setup_uart_pointer()
    {
        int mem_fd;

        if((mem_fd = open("/dev/mem", O_RDWR|O_SYNC)) < 0)
        {
            printf("can't open /dev/mem/ \n");
            exit(-1);
        }

        char * uart_map = (char *) mmap(
            NULL,
            4 * 1024,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            mem_fd,
            0x20201000
        );

        close(mem_fd);

        if((long)uart_map < 0)
        {
            printf("mmap error %p\n", uart_map);
            exit(-1);
        }

        return (volatile unsigned *) uart_map;
    }

    void Uart::setup_uart_gpio()
    {
        Gpio gpio14(14);
        Gpio gpio15(15);

        gpio14.set_alternate_function(alt0);
        gpio15.set_alternate_function(alt0);
    }

    void Uart::setup_uart_registers()
    {
        unsigned int
          * interrupt_clear_register    = (unsigned int *)(uart_base + 0x11),
          * int_baudrate_register       = (unsigned int *)(uart_base + 0x09),
          * frac_baudrate_register      = (unsigned int *)(uart_base + 0x0A),
          * line_control_register       = (unsigned int *)(uart_base + 0x0B),
          * control_register            = (unsigned int *)(uart_base + 0x0C);

        *(interrupt_clear_register)     = 0x7FF;
        *(int_baudrate_register)        = 1;
        *(frac_baudrate_register)       = 49;
        *(line_control_register)        = 0x70;
        *(control_register)             = 0x301;
    }

    Uart::Uart()
    {
        unsigned int * control_register = (unsigned int *)(uart_base + 0xC);
        *(control_register) = 0;

        setup_uart_gpio();
        setup_uart_registers();
    }

    void Uart::put(unsigned char c)
    {
        int transmit_full = 0x20;
        unsigned int
          * flag_register = (unsigned int *)(uart_base + 0x6),
          * data_register = (unsigned int *)(uart_base + 0x0);

        while(*flag_register & transmit_full);

        *(data_register) = (unsigned int) c;
    }

    unsigned char Uart::get()
    {
        int receive_empty = 0x10;
        unsigned int
          * flag_register = (unsigned int *)(uart_base + 0x6),
          * data_register = (unsigned int *)(uart_base + 0x0);
        
        while(*flag_register & receive_empty);

        unsigned char val = (unsigned char) *(data_register);
        return val;
    }
}
