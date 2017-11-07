/*
 * Davis Chen
 */


#include "mbed.h"

// length of 1 PWM cycle (in seconds)
const float PWM_PERIOD = 0.001;
const float RAMP_STEP = 0.01;

// Initialize output pins to motor driver
PwmOut motor_IN1(D3);
PwmOut motor_IN2(D4);

Serial pc(SERIAL_TX, SERIAL_RX);

/*
 * Ramps up motor from 0% to 100%
 * Arguments:
 *  ramp_duration - the amount of time in seconds that it will take to ramp from 0-100%
*/
void rampUpMotor(float ramp_duration) {
	float wait_interval = ramp_duration*RAMP_STEP;
	for (float i=0; i<1.0; i+=RAMP_STEP) {
		motor_IN1.write(i);
		wait(wait_interval);
	}
}

/*
 * Ramps down motor from 100% to 0%
 * Arguments:
 *  ramp_duration - the amount of time in seconds that it will take to ramp from 100-0%
*/
void rampDownMotor(float ramp_duration) {
	float wait_interval = ramp_duration*RAMP_STEP;
	for (float i=1.0; i>0.0; i-=RAMP_STEP) {
		motor_IN1.write(i);
		wait(wait_interval);
	}
}

int main() {
	motor_IN1.period(PWM_PERIOD);
	// set to 0; motor_IN2 is used when running motor in reverse direction
	motor_IN2.write(0);

	float ramp_up_time;
	float ramp_down_time;
	float time_at_max;

	int ramp_up_time_millis;
	int ramp_down_time_millis;
	int time_at_max_millis;

	while(1) {
		char c[8];

		int items_read = 0;
		pc.printf("Enter ramp up time: ");
		pc.gets(c, 8);
		while(sscanf(c, "%d", &ramp_up_time_millis) == 0) {
			pc.printf("\nError: Not a number\n");
			pc.printf("Enter ramp up time: ");
			pc.gets(c, 8);
		}

		pc.printf("\nEnter time at max: ");
		pc.gets(c, 8);
		while(sscanf(c, "%d", &time_at_max_millis) == 0) {
			pc.printf("\nError: Not a number\n");
			pc.printf("Enter time at max: ");
			pc.gets(c, 8);
		}

		pc.printf("\nEnter ramp down time: ");
		pc.gets(c, 8);
		while(sscanf(c, "%d", &ramp_down_time_millis) == 0) {
			pc.printf("\nError: Not a number\n");
			pc.printf("Enter ramp down time: ");
			pc.gets(c, 8);
		}

		ramp_up_time = (float) ramp_up_time_millis/1000.0;
		time_at_max = (float) time_at_max_millis/1000.0;
		ramp_down_time = (float) ramp_down_time_millis/1000.0;
		pc.printf("\n%f",ramp_up_time/1000.0);

		pc.printf("\nRamping up for %f seconds\n", ramp_up_time);
		rampUpMotor(ramp_up_time);
		pc.printf("Max output for %f seconds\n", time_at_max);
		wait(time_at_max);
		pc.printf("Ramping down for %f seconds\n", ramp_down_time);
		rampDownMotor(ramp_down_time);
		//wait(2); // this line will not be needed when user input is set up
	}
}
