#include <avr/io.h>
#include <stddef.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "servo.h"
#include "digital.h"
#include <math.h>

#define VAL_PI 3.141

int main(){
    digital_pin_mode(0,OUTPUT);
    digital_pin_mode(1,OUTPUT);
    digital_pin_mode(2,OUTPUT);
    digital_pin_mode(13,INPUT);
    timer0_init();

    while(1){
        loop();
    }
    return 0;
}

double calc_S1(double x, double y){
    return atan2(y,x)*180.0/VAL_PI;
}
double calc_S2(double x, double y, double z){
    double term1 = atan(z/sqrt(x*x+y*y));
    double term2 = acos(sqrt(x*x+y*y+z*z)/200.0);
    return (term1+term2)*180.0/VAL_PI;
}
double calc_S3(double x, double y, double z){
    double term = 2*acos(sqrt(x*x+y*y+z*z)/200.0);
    double term_angle = term*180.0/VAL_PI;
    return 155-term_angle;
}

static double x = 0;
static double y = -40;
static double z = 80;

void loop(){
    servo_set_position(0,calc_S1(x,y));
    servo_set_position(1,calc_S2(x,y,z));
    servo_set_position(2,calc_S3(x,y,z));
    // servo_set_pulse_width(0, 500);
    // servo_set_pulse_width(1, 1600);
    // servo_set_pulse_width(2, 1650);
    sei();
    uint8_t btn_state;
    digital_read(13, &btn_state);
    if(btn_state){
        y = fmod(y + 1.0, 180.0);
    }
}

