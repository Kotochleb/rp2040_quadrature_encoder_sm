#include <stdio.h>

#include "pio_rotary_encoder.h"

// initialise static encoder variables for both motors
int RotaryEncoder::rotation_motor_a = 0;
int RotaryEncoder::rotation_motor_b = 0;

// create motor object
RotaryEncoder my_encoder_a(2, 3,   MOTOR_A_SM);
RotaryEncoder my_encoder_b(26, 27, MOTOR_B_SM);

// values to keep computing motor velocity
int last_rotation_a;
int last_rotation_b;

int main() {
  // initialise serial port
  stdio_init_all();
  
  // set initial reading of encoders to 0
  my_encoder_a.set_rotation(0);
  my_encoder_b.set_rotation(0); 

  while (1) {
    // get encoder readings
    int current_rotation_a = my_encoder_a.get_rotation();
    int current_rotation_b = my_encoder_b.get_rotation();
    
    // print measurements
    printf("Motor A: %d\t", last_rotation_a - current_rotation_a);
    printf("Motor B: %d",   last_rotation_b - current_rotation_b);
    printf("\n");

    // update last values
    last_rotation_a = current_rotation_a;
    last_rotation_b = current_rotation_b;   
    sleep_ms(100);
  }
}