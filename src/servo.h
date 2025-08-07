#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>

void timer0_init(void);
void servo_add(uint8_t* port_in, uint8_t pin_in);
void servo_set_position(uint8_t servo_index, float target_position);
void servo_write(uint8_t* port_in, uint8_t pin, uint8_t high);


#endif