#include "MotorControl.h"

MotorControl::MotorControl(PinName pin1, PinName pin2) : motor_IN1(pin1), motor_IN2(pin2) {
	timer.start();
	motor_IN1.period(PWM_PERIOD);
	motor_IN2.write(0);
}

MotorControl::MotorControl(PinName pin1, PinName pin2, float rise_time_s, float on_time_s, float decay_time_s, float off_time_s, float amplitude) :
	motor_IN1(pin1),
	motor_IN2(pin2),
	rise_time_us(),
	on_time_us(),
	decay_time_us(),
	off_time_us(),
	amplitude(amplitude) {

		rise_time_us = seconds_to_microseconds(rise_time_s);
		on_time_us = seconds_to_microseconds(on_time_s);
		decay_time_us = seconds_to_microseconds(decay_time_s);
		off_time_us = seconds_to_microseconds(off_time_s);

	motor_IN1.period(PWM_PERIOD);
	motor_IN2.write(0);
	timer.start();
}

void MotorControl::rampUp() {
	static int wait_interval;
	static float duty_cycle_step;
	static float duty_cycle;
	static bool phase_start = true;
	// execute once at start of phase
	if (phase_start) {
		phase_start = false;
		wait_interval = rise_time_us/RAMP_STEPS;
		duty_cycle_step = amplitude/RAMP_STEPS;
		duty_cycle = 0;
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}


	int currentTime = timer.read_us();
	if (currentTime - prevTime >= wait_interval) {
		duty_cycle += duty_cycle_step;
		motor_IN1.write(duty_cycle);
	}
	if (currentTime - phaseStartTime >= rise_time_us) {
		currentState = running;
		phase_start = true;
	}
	
}

void MotorControl::rampDown() {
	static int wait_interval;
	static float duty_cycle_step;
	static float duty_cycle;
	static bool phase_start = true;
	// execute once at start of phase
	if (phase_start) {
		phase_start = false;
		wait_interval = decay_time_us/RAMP_STEPS;
		duty_cycle_step = amplitude/RAMP_STEPS;
		duty_cycle = amplitude;
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}


	int currentTime = timer.read_us();
	if (currentTime - prevTime >= wait_interval) {
		duty_cycle -= duty_cycle_step;
		motor_IN1.write(duty_cycle);
	}
	if (currentTime - phaseStartTime >= decay_time_us) {
		currentState = stopped;
		phase_start = true;
	}
}

void MotorControl::runMotor() {
	static bool phase_start = true;
	// execute once at start of phase
	if (phase_start) {
		phase_start = false;
		motor_IN1.write(amplitude);
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	int currentTime = timer.read_us();
	if (currentTime - phaseStartTime >= on_time_us) {
		currentState = rampDown;
		phase_start = true;
	}
}

void MotorControl::stopMotor() {
	static bool phase_start = true;
	// execute once at start of phase
	if (phase_start) {
		phase_start = false;
		motor_IN1.write(0);
		prevTime = timer.read_us();
	}

	int currentTime = timer.read_us();
	if (currentTime - prevTime >= off_time_us) {
		phase_start = true;
		if (repeat)
			currentState = rampUp;
		else
			currentState = off;
	}
}

static int seconds_to_microseconds(int n) {
	if (n < 0)
		return 0;
	// 1 million microseconds in a second
	return n/1000000;
}

void MotorControl::setRampUpTime_s(float time_s) {
	rise_time_us = seconds_to_microseconds(time_s);
}


void MotorControl::setRampDownTime_s(float time_s) {
	decay_time_us = seconds_to_microseconds(time_s);
}

void MotorControl::setOnTime_s(float time_s) {
	on_time_us = seconds_to_microseconds(time_s);
}

void MotorControl::setOffTime_s(float time_s) {
	off_time_us = seconds_to_microseconds(time_s);
}

void MotorControl::setAmplitude(float value) {amplitude = value;}

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
