#include <stdio.h>

#include "hardware/pio.h"
#include "hardware/irq.h"

#include "pio_rotary_encoder.h"
#include "pio_rotary_encoder.pio.h"


RotaryEncoder::RotaryEncoder(uint rotary_encoder_A, uint rotary_encoder_B, uint sm_num) {
    gpio_set_pulls(rotary_encoder_A, true, false);
    gpio_set_pulls(rotary_encoder_B, true, false);

    sm = sm_num;

    if (sm == 0) {
        PIO pio = pio0;
        pio_gpio_init(pio, rotary_encoder_A);
        pio_gpio_init(pio, rotary_encoder_B);
        uint offset = pio_add_program(pio, &pio_rotary_encoder_program);
        pio_sm_config c = pio_rotary_encoder_program_get_default_config(offset);
        sm_config_set_in_pins(&c, rotary_encoder_A);
        sm_config_set_in_shift(&c, false, false, 0);
        irq_set_exclusive_handler(PIO0_IRQ_0, pio_0_irq_handler);
        irq_set_enabled(PIO0_IRQ_0, true);
        pio0_hw->inte0 = PIO_IRQ0_INTE_SM0_BITS | PIO_IRQ0_INTE_SM1_BITS;
        pio_sm_init(pio, sm, 16, &c);
        pio_sm_set_enabled(pio, sm, true);
    }
    else if (sm == 1) {
        PIO pio = pio1;
        pio_gpio_init(pio, rotary_encoder_A);
        pio_gpio_init(pio, rotary_encoder_B);
        uint offset = pio_add_program(pio, &pio_rotary_encoder_program);
        pio_sm_config c = pio_rotary_encoder_program_get_default_config(offset);
        sm_config_set_in_pins(&c, rotary_encoder_A);
        sm_config_set_in_shift(&c, false, false, 0);
        irq_set_exclusive_handler(PIO1_IRQ_1, pio_1_irq_handler);
        irq_set_enabled(PIO1_IRQ_1, true);
        pio1_hw->inte1 = PIO_IRQ1_INTE_SM0_BITS | PIO_IRQ1_INTE_SM1_BITS;
        pio_sm_init(pio, sm, 16, &c);
        pio_sm_set_enabled(pio, sm, true);
    }
}

// set the current rotation to a specific value
void RotaryEncoder::set_rotation(int _rotation) {
    if (sm == MOTOR_A_SM) {
        rotation_motor_a = _rotation;
    }
    else if (sm == MOTOR_B_SM) {
        rotation_motor_b = _rotation;
    }
}

// get the current rotation
int RotaryEncoder::get_rotation(void) {
    if (sm == MOTOR_A_SM) {
        return rotation_motor_a;
    }
    else if (sm == MOTOR_B_SM) {
        return rotation_motor_b;
    }
}

