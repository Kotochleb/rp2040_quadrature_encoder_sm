#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/irq.h"

#include "pio_rotary_encoder.h"
#include "pio_rotary_encoder.pio.h"


RotaryEncoder::RotaryEncoder(uint rotary_encoder_A)
{
    uint8_t rotary_encoder_B = rotary_encoder_A + 1;
    // pio 0 is used
    PIO pio = pio0;
    // state machine 0
    uint8_t sm = 0;
    // configure the used pins as input with pull up
    pio_gpio_init(pio, rotary_encoder_A);
    gpio_set_pulls(rotary_encoder_A, true, false);
    pio_gpio_init(pio, rotary_encoder_B);
    gpio_set_pulls(rotary_encoder_B, true, false);
    // load the pio program into the pio memory
    uint offset = pio_add_program(pio, &pio_rotary_encoder_program);
    // make a sm config
    pio_sm_config c = pio_rotary_encoder_program_get_default_config(offset);
    // set the 'in' pins
    sm_config_set_in_pins(&c, rotary_encoder_A);
    // set shift to left: bits shifted by 'in' enter at the least
    // significant bit (LSB), no autopush
    sm_config_set_in_shift(&c, false, false, 0);
    // set the IRQ handler
    irq_set_exclusive_handler(PIO0_IRQ_0, pio_irq_handler);
    // enable the IRQ
    irq_set_enabled(PIO0_IRQ_0, true);
    pio0_hw->inte0 = PIO_IRQ0_INTE_SM0_BITS | PIO_IRQ0_INTE_SM1_BITS;
    // init the sm.
    // Note: the program starts after the jump table -> initial_pc = 16
    pio_sm_init(pio, sm, 16, &c);
    // enable the sm
    pio_sm_set_enabled(pio, sm, true);
}

// set the current rotation to a specific value
void RotaryEncoder::set_rotation(int _rotation)
{
    rotation = _rotation;
}

// get the current rotation
int RotaryEncoder::get_rotation(void)
{
    return rotation;
}

