#include "mbed.h"

// Initialize pins
DigitalOut motor_IN2(D10);
PwmOut motor_IN1(D3);

int main() {
	float waittime = 2.0;
	motor_IN2 = 0;
	motor_IN1.period(0.001f);
	float outputCycle = 0.0;

    while(1) {
		// Ramp up output from 0-100% in 10% increments
    	motor_IN1.write(outputCycle);
		if (outputCycle <= 0.9)
			outputCycle += 0.1;
		else
			outputCycle = 0.0;
		wait(waittime);
    }
}

