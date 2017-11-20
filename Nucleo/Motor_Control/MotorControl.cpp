#include "MotorControl.h"

MotorControl::MotorControl(PinName pin1, PinName pin2) : motor_IN1(pin1), motor_IN2(pin2) {
	timer.start();
	motor_IN1.period(PWM_PERIOD);
	motor_IN2.write(0);
}

MotorControl::MotorControl(PinName pin1, PinName pin2, float rise_time, float on_time, float decay_time, float off_time, float amplitude) :
	motor_IN1(pin1),
	motor_IN2(pin2),
	rise_time(rise_time),
	on_time(on_time),
	decay_time(decay_time),
	off_time(off_time),
	amplitude(amplitude) {

	timer.start();
	motor_IN1.period(PWM_PERIOD);
	motor_IN2.write(0);
}

void MotorControl::rampUp() {
	static int wait_interval = rise_time/RAMP_STEPS;
	static float step_size = amplitude/RAMP_STEPS;
	static float duty_cycle = 0;
	// execute once at start of phase
	if (prevState != rampUp) {
		prevState =rampUp;
		wait_interval = rise_time/RAMP_STEPS;
		step_size = amplitude/RAMP_STEPS;
		duty_cycle = 0;
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	int currentTime = timer.read_us();
	if (currentTime - prevTime >= wait_interval) {
		duty_cycle += step_size;
		motor_IN1.write(duty_cycle);
	}
	if (currentTime - phaseStartTime >= rise_time) {
		currentState = running;
	}
	
}

void MotorControl::rampDown() {
	// execute once at start of phase
	if (prevState != rampDown) {
		prevState = rampDown;
		prevTime = timer.read_us();
	}
}

void MotorControl::runMotor() {
	// execute once at start of phase
	if (prevState != running) {
		motor_IN1.write(amplitude);
		prevState = running;
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	int currentTime = timer.read_us();
	if (currentTime - phaseStartTime >= on_time) {
		currentState = rampDown;
	}
}

void MotorControl::stopMotor() {
	// execute once at start of phase
	if (prevState != stopped) {
		motor_IN1.write(0);
		prevState = stopped;
		prevTime = timer.read_us();
	}

	int currentTime = timer.read_us();
	if (currentTime - prevTime >= off_time) {
		if (repeat)
			currentState = rampUp;
		else
			currentState = off;
	}
}

void setRampUpTime(float value) {rise_time = value;}
void setRampDownTime(float value) {decay_time = value;}
void setOnTime(float value) {on_time = value;}
void setOffTime(float value) {off_time = value;}

void setAmplitude(float value) {amplitude = value;}

void MotorControl::run() {
	switch(currentState) {
		case rampUp:
			rampUp();
			break;
		case rampDown:
			rampDown();
			break;
		case running:
			runMotor();
			break;
		case stopped:
			stopMotor();
			break;
		default:
			break;
	}
}
