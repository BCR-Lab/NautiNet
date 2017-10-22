#include "mbed.h"

// length of 1 PWM cycle (in seconds)
const float PWM_PERIOD = 0.001;

// these should be set up by user input
const float RAMP_UP_TIME = 5.0;
const float RAMP_DOWN_TIME = 5.0;
const float TIME_AT_MAX = 2.5;

// Initialize output pins to motor driver
PwmOut motor_IN1(D3);
PwmOut motor_IN2(D4);

/*
 * Ramps up motor from 0% to 100%
 * Input:
 *  ramp_time - the amount of time in seconds that it will take to ramp from 0-100%
*/
void rampUpMotor(float ramp_time) {
	float wait_interval = ramp_time/ramp_step;
	for (int i=0; i<1.0; i+=ramp_step) {
		motor_IN1.write(i);
		wait(wait_interval);
	}
}

/*
 * Ramps down motor from 100% to 0%
 * Input:
 *  ramp_time - the amount of time in seconds that it will take to ramp from 100-0%
*/
void rampDownMotor(float ramp_time) {
	float wait_interval = ramp_time/ramp_step;
	for (int i=1.0; i>0.0; i-=ramp_step) {
		motor_IN1.write(i);
		wait(wait_interval);
	}
}

int main() {
	motor_IN1.period(PWM_PERIOD);
	// set to 0; motor_IN2 is used when running motor in reverse direction
	motor_IN2.write(0);

	while(1) {
		rampUpMotor(RAMP_UP_TIME);
		wait(TIME_AT_MAX);
		rampDownMotor(RAMP_DOWN_TIME);
		wait(5); // this line will not be needed when user input is set up
	}
}


