#ifndef __PIO_ROTARY_ENCODER_H__
#define __PIO_ROTARY_ENCODER_H__

#include <stdio.h>

#include "hardware/pio.h"
#include "hardware/irq.h"

class RotaryEncoder
{
public:
    RotaryEncoder(uint rotary_encoder_A);
    void set_rotation(int _rotation);
    int get_rotation(void);

private:
    static void pio_irq_handler();
    PIO pio;
    uint sm;
    static int rotation;
};

#endif // __PIO_ROTARY_ENCODER_H__