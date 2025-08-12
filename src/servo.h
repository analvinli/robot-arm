#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>

void timer0_init(void);
void servo_add(volatile uint8_t* port_in, uint8_t pin_in);
void servo_set_position(uint8_t servo_index, double target_position);
void servo_write(volatile uint8_t* port_in, uint8_t pin, uint8_t high);
void servo_set_pulse_width(uint8_t servo_index, uint16_t target_pulse_width_us);

#endif