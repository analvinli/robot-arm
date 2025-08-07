#include "servo.h"
#include <avr/io.h>
#include <stddef.h>
#include <avr/interrupt.h>

#define MIN_DUTY_US 500
#define MAX_DUTY_US 2500
#define PWM_PERIOD_US 20000

typedef struct{
    volatile uint8_t* port;
    uint8_t pin;
    uint16_t pulse_width;//500 to 2500 us
}Servo;

static Servo* servo_arr = NULL;
static uint8_t servo_count = 0;
uint16_t elapsed_time_us = 0; //max 20,000us or 20ms

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

    //set default servo values
    servo_arr[servo_count-1].port = port_in;
    servo_arr[servo_count-1].pin = pin_in;
    servo_arr[servo_count-1].pulse_width = 0;
    return;
}

void servo_set_position(uint8_t servo_index, float target_position){//target_position in degrees: [0,180]
    if(target_position>180){
        return;
    }
    //map target degree to pulse width
    uint16_t pulse_width_us = (uint16_t)((target_position/180.0)*2000+MIN_DUTY_US);
    servo_arr[servo_index].pulse_width = pulse_width_us;
    return;
}

void servo_write(uint8_t* port_in, uint8_t pin, uint8_t high){
    if(high){
        *port_in |= (1<<pin);
        return;
    }
    *port_in &= ~(1<<pin);
    return;
}

//every 16us
ISR(TIMER0_OVF_vect) {
    elapsed_time_us+=16;
    if(elapsed_time_us <= MAX_DUTY_US){
        for(int i = 0;i<servo_count;i++){
            if(elapsed_time_us>=servo_arr[i].pulse_width){
                //turn off when duty cycle is up
                servo_write(servo_arr[i].port, servo_arr[i].pin, 0);
            }
        }
    }

    if(elapsed_time_us >= PWM_PERIOD_US){
        //end of period
        elapsed_time_us = 0;

        //start of period
        for(int j = 0;j<servo_count;j++){//set all servos high
            servo_write(servo_arr[j].port, servo_arr[j].pin, 1);
        }
    }
}