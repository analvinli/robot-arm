#include "servo.h"
#include <avr/io.h>
#include <stddef.h>
#include <avr/interrupt.h>

typedef struct{
    volatile uint8_t* port;
    uint8_t pin;
    uint16_t pulse_width;//500 to 2500 us
}Servo;

static Servo* servo_arr = NULL;
static uint8_t servo_count = 0;

void timer0_init(void){
    TCCR0B = (1 << CS00);
    TIMSK0 = (1 << TOIE0);
    TCNT0 = 0;
    sei();
}

void servo_add(uint8_t* port_in, uint8_t pin_in){
    Servo* temp_arr = realloc(servo_arr, (++servo_count)*sizeof(Servo));
    if(temp_arr==NULL){
        return;//not enough memory
    }
    servo_arr = temp_arr;

    servo_arr[servo_count-1].port = port_in;
    servo_arr[servo_count-1].pin = pin_in;
    servo_arr[servo_count-1].pulse_width = 0;
    return;
}

void servo_set_position(uint8_t servo_index, uint8_t target_position){

}

//every 16us
ISR(TIMER0_OVF_vect) {

}