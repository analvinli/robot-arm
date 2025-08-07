#include "digital.h"
#include <avr/io.h>
#include <stddef.h>

volatile uint8_t *digital_pin_to_port(uint8_t pin){
    if(pin > 19){
        return NULL;
    }
    return (volatile uint8_t*)((int)&PORTD - 6*(pin>7) + 3*(pin>13));
}

volatile uint8_t *digital_port_offset(volatile uint8_t * const port, digital_register_type_t type){
    return (volatile uint8_t*)((int)port - type);
}

int digital_pin_to_bit(uint8_t pin){
    if(pin>19){
        return -1;
    }if(pin>13){
        return pin-14;
    }if(pin>7){
        return pin-8;
    }
    return pin;
}

bool digital_pin_mode(uint8_t pin, digital_mode_t mode){
    uint8_t* port = digital_port_offset(digital_pin_to_port(pin),DDRx);
    int bit_offset = digital_pin_to_bit(pin);
    if(mode==OUTPUT){
        *port |= (1<<bit_offset); //bit to 1
        if(*port>>bit_offset){//checks if LSB after shift is 1
            return true;
        }return false;
    }if(mode==INPUT){
        *port &= !(1<<bit_offset);//bit to 0
        if(!(*port>>bit_offset)){//checks if LSB after shift is 0
            return true;
        }return false;
    }
    return false;
}

bool digital_write(uint8_t pin, bool high){
    uint8_t* port = digital_port_offset(digital_pin_to_port(pin),PORTx);
    int bit_offset = digital_pin_to_bit(pin);
    if(high){
        *port |= (1<<bit_offset);
        if(*port>>bit_offset){
            return true;
        }return false;
    }if(!high){
        *port &= !(1<<bit_offset);
        if(!(*port>>bit_offset)){
            return true;
        }return false;
    }
    return false;
}

bool digital_read(uint8_t pin, bool * const pin_state){
    uint8_t* port = digital_port_offset(digital_pin_to_port(pin),PINx);
    int bit_offset = digital_pin_to_bit(pin);
    
    *pin_state = (*port & (1<<bit_offset))?1:0;
    if(*pin_state == (*port<<bit_offset)){
        return true;
    }return false;
}