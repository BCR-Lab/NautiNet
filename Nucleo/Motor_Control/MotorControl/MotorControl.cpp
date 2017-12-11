#include "MotorControl.h"

static int seconds_to_microseconds(float &n) {
	if (n < 0)
		return 0;
	// 1 million microseconds in a second
	return n*1000000;
}

MotorControl::MotorControl(PinName pin) : motor_IN1(pin1), motor_IN2(pin2) {
	timer.start();
	motor_IN.period_us(PWM_PERIOD_US);
}

MotorControl::MotorControl(PinName pin, float rise_time_s, float on_time_s, float decay_time_s, float off_time_s, float amplitude) :
	motor_IN(pin),
	rise_time_us(),
	on_time_us(),
	decay_time_us(),
	off_time_us(),
	amplitude(amplitude) {

	rise_time_us = seconds_to_microseconds(rise_time_s);
	on_time_us = seconds_to_microseconds(on_time_s);
	decay_time_us = seconds_to_microseconds(decay_time_s);
	off_time_us = seconds_to_microseconds(off_time_s);

	motor_IN.period_us(PWM_PERIOD_US);
	timer.start();
}

/*
 * Function name: rampUpMotor
 * Description: Ramps up motor linearly from 0 to the set amplitude over rise_time_us microseconds.
 * Arguments: N/A
 * Return value: N/A
 * Note: The rise time can be set using the setRampUpTime_s member function
 */
void MotorControl::rampUpMotor() {
	// execute once at start of phase
	if (ramp_up_phase_start) {
		ramp_up_phase_start = false;
		ramp_up_wait_interval = rise_time_us/RAMP_STEPS;
		ramp_up_duty_cycle_step = amplitude/RAMP_STEPS;
		ramp_up_duty_cycle = 0;
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}


	int currentTime = timer.read_us();
	if (currentTime - prevTime >= ramp_up_wait_interval) {
		prevTime = currentTime;
		ramp_up_duty_cycle += ramp_up_duty_cycle_step;
		motor_IN1.write(ramp_up_duty_cycle);
	}
	if (currentTime - phaseStartTime >= rise_time_us) {
		currentState = running;
		ramp_up_phase_start = true;
	}

}

void MotorControl::rampDownMotor() {
	// execute once at start of phase
	if (ramp_down_phase_start) {
		ramp_down_phase_start = false;
		ramp_down_wait_interval = decay_time_us/RAMP_STEPS;
		ramp_down_duty_cycle_step = amplitude/RAMP_STEPS;
		ramp_down_duty_cycle = amplitude;
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	int currentTime = timer.read_us();
	if (currentTime - prevTime >= ramp_down_wait_interval) {
		prevTime = currentTime;
		ramp_down_duty_cycle -= ramp_down_duty_cycle_step;
		motor_IN1.write(ramp_down_duty_cycle);
	}
	if (currentTime - phaseStartTime >= decay_time_us) {
		currentState = stopped;
		ramp_down_phase_start = true;
	}
}

void MotorControl::runMotor() {
	// execute once at start of phase
	if (running_phase_start) {
		running_phase_start = false;
		motor_IN1.write(amplitude);
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	int currentTime = timer.read_us();
	if (currentTime - phaseStartTime >= on_time_us) {
		currentState = rampDown;
		running_phase_start = true;
	}
}

void MotorControl::stopMotor() {
	// execute once at start of phase
	if (stopped_phase_start) {
		stopped_phase_start = false;
		motor_IN1.write(0);
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	int currentTime = timer.read_us();
	if (currentTime - phaseStartTime >= off_time_us) {
		stopped_phase_start = true;
		if (repeat)
			currentState = rampUp;
		else
			currentState = off;
	}
}

void MotorControl::setRampUpTime_s(float &time_s) {
	rise_time_us = seconds_to_microseconds(time_s);
}

void MotorControl::setRampDownTime_s(float &time_s) {
	decay_time_us = seconds_to_microseconds(time_s);
}

void MotorControl::setOnTime_s(float &time_s) {
	on_time_us = seconds_to_microseconds(time_s);
}

void MotorControl::setOffTime_s(float &time_s) {
	off_time_us = seconds_to_microseconds(time_s);
}

void MotorControl::setAmplitude(float &value) {
	amplitude = value;
}

void MotorControl::setRepeat(bool value) {
	repeat = value;
}

void MotorControl::run() {
	switch(currentState) {
		case rampUp:
			rampUpMotor();
			break;
		case rampDown:
			rampDownMotor();
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

void MotorControl::start() {
	currentState = rampUp;
}
