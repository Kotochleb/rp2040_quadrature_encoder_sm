#ifndef __PIO_ROTARY_ENCODER_H__
#define __PIO_ROTARY_ENCODER_H__

#include <stdio.h>

#include "hardware/pio.h"
#include "hardware/irq.h"

#define MOTOR_A_SM 0
#define MOTOR_B_SM 1

class RotaryEncoder {
public:
    RotaryEncoder(uint rotary_encoder_A, uint rotary_encoder_B, uint sm_num);
    void set_rotation(int _rotation);
    int get_rotation(void);

private:
    static void pio_0_irq_handler()
    {
        // test if irq 0 was raised
        if (pio0_hw->irq & 1)
        {
            rotation_motor_a--;
        }
        // test if irq 1 was raised
        if (pio0_hw->irq & 2)
        {
            rotation_motor_a++;
        }
        // clear both interrupts
        pio0_hw->irq = 3;
    }

    static void pio_1_irq_handler()
    {
        // test if irq 0 was raised
        if (pio1_hw->irq & 1)
        {
            rotation_motor_b--;
        }
        // test if irq 1 was raised
        if (pio1_hw->irq & 2)
        {
            rotation_motor_b++;
        }
        // clear both interrupts
        pio1_hw->irq = 3;
    }

    uint sm;
    static int rotation_motor_a;
    static int rotation_motor_b;
};

#endif // __PIO_ROTARY_ENCODER_H__