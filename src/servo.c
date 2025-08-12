#include "servo.h"
#include <avr/io.h>
#include <stddef.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define PWM_PERIOD_US 20000
#define INTERRUPT_ERROR_US 16

typedef struct{
    volatile uint8_t* port;
    uint8_t pin;
    uint16_t pulse_width;
    uint16_t min_pulse;
    uint16_t max_pulse;
}Servo;

static Servo servo_array[3] = {
    {&PORTD, 0, 0, 500, 1600},
    {&PORTD, 1, 0, 500, 1650},
    {&PORTD, 2, 0, 500, 1650},
};
static uint8_t servo_count = sizeof(servo_array) / sizeof(Servo);
uint16_t elapsed_time_us = 0;

void timer0_init(void){
    TCCR0B = (1 << CS00);
    TIMSK0 = (1 << TOIE0);
    TCNT0 = 0;
}

void servo_set_pulse_width(uint8_t servo_index, uint16_t target_pulse_width_us){
    switch(servo_index){
        case 0:
            servo_array[0].pulse_width = target_pulse_width_us;
            return;
        case 1:
            servo_array[1].pulse_width = target_pulse_width_us;
            return;
        case 2:{
            uint16_t minimum_pulse = servo_array[servo_index].min_pulse;
            uint16_t maximum_pulse = servo_array[servo_index].max_pulse;
            servo_array[2].pulse_width = (maximum_pulse-target_pulse_width_us)+minimum_pulse;
            return;
        }
    }
}

void servo_set_position(uint8_t servo_index, double target_position){ //target_position in degrees: [0,180]
    if(target_position>180||servo_index>=servo_count){
        return;
    }
    //map target degree to pulse width
    uint16_t minimum_pulse = servo_array[servo_index].min_pulse;
    uint16_t maximum_pulse = servo_array[servo_index].max_pulse;
    uint16_t pulse_width_us = (uint16_t)(((target_position/180.0)*(maximum_pulse-minimum_pulse))+minimum_pulse);

    servo_set_pulse_width(servo_index, pulse_width_us);
    return;
}

void servo_write(volatile uint8_t* port_in, uint8_t pin, uint8_t high){
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
    if(elapsed_time_us <= 2000){
        for(int i = 0;i<servo_count;i++){
            if(elapsed_time_us>=servo_array[i].pulse_width){
                testfunc();
                //turn off when duty cycle is up
                servo_write(servo_array[i].port, servo_array[i].pin, 0);
            }
        }
    }

    if(elapsed_time_us >= PWM_PERIOD_US){
        testfunc();
        //end of period
        elapsed_time_us = 0;

        //start of period
        for(int j = 0;j<servo_count;j++){//set all servos high
            servo_write(servo_array[j].port, servo_array[j].pin, 1);
        }
    }
}

void testfunc(){
    return;
}