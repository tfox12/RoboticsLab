#include "vex_interface.h"
#include "uart.h"

static Uart uart_interface;

const static unsigned char SET_MOTOR_VALUE_FID      = 0;
const static unsigned char GET_SENSOR_VALUE_FID     = 1;

static inline void WRITE8(unsigned char val)
{
    uart_interface.put(val);
}

static inline void WRITE16(unsigned short val)
{
    uart_interface.put((char)(val>>8));
    uart_interface.put((char)(val>>0));
}

static inline void WRITE32(unsigned int val)
{
    uart_interface.put((char)(val>>24));
    uart_interface.put((char)(val>>16));
    uart_interface.put((char)(val>>8));
    uart_interface.put((char)(val>>0));
}

static inline unsigned char READ8()
{
    return uart_interface.get();
}

static inline unsigned short READ16()
{
    unsigned short return_value = 0;

    return_value |= ((unsigned short)uart.get()) << 8;
    return_value |= ((unsigned short)uart.get()) << 0;

    return return_value;
}

static inline unsigned int READ32()
{
    unsigned int return_value = 0;

    return_value |= ((unsigned short)uart.get()) << 24;
    return_value |= ((unsigned short)uart.get()) << 16;
    return_value |= ((unsigned short)uart.get()) << 8;
    return_value |= ((unsigned short)uart.get()) << 0;

    return return_value;
}

void set_motor_value(unsigned char port, short value)
{
    WRITE8(SET_MOTOR_VALUE_FID);
    WRITE8(port);
    WRITE16(value);
}

short get_sensor_value(unsigned char port)
{
    WRITE8(GET_SENSOR_VALUE_FID);
    WRITE8(port);
    return READ16();
}

