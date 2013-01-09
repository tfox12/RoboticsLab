#include "gpio.h"

#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstdio>

namespace RaspberryPi
{
    Gpio::Gpio(unsigned char pin) : pin_number(pin) { }

    void Gpio::set_alternate_function(alternate_function alt)
    {
        GpioInterface * gi = GpioInterface::instance();

        /*
         * Each word of the function select registers stores data for
         * 10 gpio pins. So the word offset for the current pin is the
         * pin number divided by 10, using int division
         */
        volatile unsigned * word_offset = gi->gpio_base + pin_number * 4 / 10;
        
        /*
         * Each pin gets 3 bits for its function id
         * we reset the bits of the current pin by 'and'ing
         * the 3 bits, followed by 'or'ing the new function
         * bits into its place
         */ 
        *word_offset &= ~(7<<(pin_number%10));
        *word_offset |= (alt<<(pin_number%10));
    }

    // sets the pin as high
    void Gpio::set()
    {
        GpioInterface * gi = GpioInterface::instance();
        int set_offset = 0x1c;
        
        /*
         * Each pin gets 1 bit, so we just shift a 1 by
         * the pin number
         */
        *(gi->gpio_base + set_offset + pin_number / 32) = 1 << (pin_number % 32); 
    }

    // sets the pin as low
    void Gpio::clear()
    {
        GpioInterface * gi = GpioInterface::instance();
        int clear_offset = 0x28;
        
        /*
         * Each pin gets 1 bit, so we just shift a 1 by
         * the pin number
         */
        *(gi->gpio_base + clear_offset + pin_number / 32) = 1 << (pin_number % 32); 
    }

    GpioInterface::GpioInterface()
    {
        int mem_fd;

        /* open /dev/mem */
        if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0)
        {
           printf("can't open /dev/mem \n");
           exit(-1);
        }
 
        /* mmap GPIO */
        char * gpio_map = (char *) mmap(
           NULL,             //Any adddress in our space will do
           4 * 1024,       //Map length
           PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
           MAP_SHARED,       //Shared with other processes
           mem_fd,           //File to map
           0x20200000         //Offset to GPIO peripheral
        );
 
        close(mem_fd); //No need to keep mem_fd open after mmap
 
        if ((long)gpio_map < 0) {
           printf("mmap error %p\n", gpio_map);
           exit(-1);
        }
 
        // Always use volatile pointer!
        gpio_base = (volatile unsigned *)gpio_map;
 
    }

    GpioInterface * GpioInterface::INSTANCE = new GpioInterface;

    GpioInterface * GpioInterface::instance() { return INSTANCE; }

}
