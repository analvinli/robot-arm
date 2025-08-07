#include <avr/io.h>
#include <stddef.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "digital.h"

void main(){
    digital_pin_mode(3,OUTPUT);
    


    while(1){
        loop();
    }
}

//0.5-2.5

void loop(){
    // digital_write(3,1);
    // _delay_ms(0.5);
    // digital_write(3,0);
    // _delay_ms(19.5);

    digital_write(3,1);
    _delay_ms(2.5);
    digital_write(3,0);
    _delay_ms(17.5);
}