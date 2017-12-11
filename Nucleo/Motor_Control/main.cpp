/*
 * Davis Chen
 */

#include "mbed.h"
#include "MotorControl.h"

int main() {

	MotorControl m1(D3, 0.5, 0.5, 0.5, 0.5, 0.2);
	MotorControl m2(D9, 1, 1, 1, 1, 0.2);
	m1.start();
	m2.start();

	while(1) {
		m1.run();
		m2.run();
		// run other code here (check sensors, change parameters)
	}
}
