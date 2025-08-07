#include <avr/io.h>
#include <stddef.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "servo.h"

void main(){
    DDRB |= (1<<PB5);
    timer0_init();
    servo_add(&PORTD,3);

    while(1){
        loop();
    }
    return 0;
}

//0.5 to 2.5 ms pulse len
//500 to 2500 us pulse len
//-90 to +90 degrees, 

//with timer0 and no div factor, timer0 overflows every 16 us
//2000us/16us = 125 positions
//180degrees/125 = 1.44 degrees of resolution


void loop(){
    servo_set_position(0,0);
    
}