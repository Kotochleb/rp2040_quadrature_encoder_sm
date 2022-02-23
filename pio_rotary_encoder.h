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
    static void pio_irq_handler()
    {
        // test if irq 0 was raised
        if (pio0_hw->irq & 1)
        {
            rotation = rotation - 1;
        }
        // test if irq 1 was raised
        if (pio0_hw->irq & 2)
        {
            rotation = rotation + 1;
        }
        // clear both interrupts
        pio0_hw->irq = 3;
    }

    PIO pio;
    uint sm;
    static int rotation;
};

#endif // __PIO_ROTARY_ENCODER_H__