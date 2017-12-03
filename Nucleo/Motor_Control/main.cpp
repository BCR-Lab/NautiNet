/*
 * Davis Chen
 */

#include "mbed.h"
#include "MotorControl.h"

int main() {
	MotorControl m1(D9,D5, 1, 0, 1, 1, .5);
	m1.start();
	MotorControl m2(D10,D6, 1, 3, 1, 1, 1.0);
	m2.start();

	while(1) {
		m1.run();
		m2.run();
	}
}
