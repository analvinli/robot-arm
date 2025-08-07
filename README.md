# test-repo
using SG90 servos
pulse length ranges from 500us to 2500us (microseconds)
pwm period is 20ms or 20,000 us

500us -> 0 degrees/leftmost position
2500us -> 180 degrees/rightmost position

uses timer0 with clock div factor of 1
timer0 is 8-bit, thus overflows every 16 microseconds

2000us/16us = 125 possible positions
180degrees/125 = 1.44 degrees of resolution