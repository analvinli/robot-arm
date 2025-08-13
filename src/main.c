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
    digital_pin_mode(12,INPUT);
    timer0_init();

    while(1){
        loop();
    }
    return 0;
}

static double x = 40;
static double y = 0;
static double z = 20;
static double r_xy = 0;
static double r_xyz = 0;

double calc_S1(double x, double y){
    return atan2(y,x)*180.0/VAL_PI;
}
double calc_S2(double x, double y, double z){
    double term1 = atan(z/r_xy);
    double term2 = acos(r_xyz/200.0);
    return (term1+term2)*180.0/VAL_PI;
}
double calc_S3(double x, double y, double z){
    double term = 2*acos(r_xyz/200.0);
    double term_angle = term*180.0/VAL_PI;
    return 155-term_angle;
}

void calc_r(double x, double y, double z){
    r_xy = sqrt(x*x+y*y);
    r_xyz = sqrt(x*x+y*y+z*z);
}

void loop(){
    // calc_r(x,y,z);
    // servo_set_position(0,calc_S1(x,y));
    // servo_set_position(1,calc_S2(x,y,z));
    // servo_set_position(2,calc_S3(x,y,z));

    // servo_set_pulse_width(0, 500);
    // servo_set_pulse_width(1, 1600);
    servo_set_pulse_width(2, 1600);


    // uint8_t btn_state;
    // uint8_t btn2_state;
    // digital_read(13, &btn_state);
    // digital_read(12, &btn2_state);
    // if(btn_state){
    //     x = 150;
    // }
    // if(btn2_state){
    //     x = 40;
    // }
}

