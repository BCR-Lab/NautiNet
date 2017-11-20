#include "MotorControl.h"

MotorControl::MotorControl(PinName pin1, PinName pin2) : motor_IN1(pin1), motor_IN2(pin2) {}

MotorControl::MotorControl(PinName pin1, PinName pin2, float rise_time, float on_time, float decay_time, float off_time, float amplitude) :
	motor_IN1(pin1),
	motor_IN2(pin2),
	rise_time(rise_time),
	on_time(on_time),
	decay_time(decay_time),
	off_time(off_time),
	amplitude(amplitude)
{
	timer.start();
}

void MotorControl::rampUp() {
	float wait_interval = rise_time/RAMP_STEPS;
	float step_size = amplitude/RAMP_STEPS;
	
}

void MotorControl::rampDown() {
}

void MotorControl::runMotor() {
	int currentTime = timer.read_us();
}

void MotorControl::stopMotor() {
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
