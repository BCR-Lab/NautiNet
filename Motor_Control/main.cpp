#include "mbed.h"

DigitalOut myled(LED1);
//DigitalOut motor_IN1(D3);
DigitalOut motor_IN2(D10);

PwmOut in1(D3);
//PwmOut in2(D10);


int main() {
	float waittime = 2.0;
	myled = 1;
	motor_IN2 = 0;
	//in1.period(0.020f);
	float outputCycle = 0.0;

    while(1) {
		myled = !myled;
		//motor_IN1 = myled;
		//motor_IN2 = myled;
    	in1.write(outputCycle);
		if (outputCycle <= 0.9)
			outputCycle += 0.1;
		else
			outputCycle = 0.0;
		wait(waittime);
    }
}

