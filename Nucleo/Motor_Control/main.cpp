/*
 * Davis Chen
 * Description: A simple program to test the MotorControl class
 */

#include "mbed.h"
#include "MotorControl.h"

int main() {
	// set each phase to be 0.5 seconds long, with an ammplitude of 100%
	MotorControl motor1(D4, 0.5, 0.5, 0.5, 0.5, 1);
	motor1.start();

	while(1) {
		motor1.run();
		// run other code here (check sensors, change motor cycle parameters)
	}
}
