#include "MotorControl.h"

static int seconds_to_microseconds(const float &n) {
	if (n < 0)
		return 0;
	// 1 million microseconds in a second
	return n*1000000;
}

MotorControl::MotorControl(PinName pin) : motor_IN(pin){
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
 * Note: rise_time_us can be set using the setRiseTime_s method
 */
void MotorControl::rampUpMotor() {
	// initialize phase variables
	// execute once at start of phase
	if (ramp_up_phase_begin) {
		ramp_up_phase_begin = false;
		ramp_up_wait_interval = rise_time_us/RAMP_STEPS;
		ramp_up_duty_cycle_step = amplitude/RAMP_STEPS;
		duty_cycle = 0;
		motor_IN.write(duty_cycle);
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	currentTime = timer.read_us();
	if (currentTime - prevTime >= ramp_up_wait_interval) {
		// increment PWM duty cycle
		prevTime = currentTime;
		duty_cycle += ramp_up_duty_cycle_step;
		motor_IN.write(duty_cycle);
	}
	if (currentTime - phaseStartTime >= rise_time_us) {
		// end phase, set state to next phase
		currentState = running;
		ramp_up_phase_begin = true;
	}

}

/*
 * Function name: rampDownMotor
 * Description: Ramps down motor linearly from the set amplitude to 0 over decay_time_us microseconds.
 * Arguments: N/A
 * Return value: N/A
 * Note: decay_time_us can be set using the setDecayTime_s method
 */
void MotorControl::rampDownMotor() {
	// initialize phase variables
	// execute once at start of phase
	if (ramp_down_phase_begin) {
		ramp_down_phase_begin = false;
		ramp_down_wait_interval = decay_time_us/RAMP_STEPS;
		ramp_down_duty_cycle_step = amplitude/RAMP_STEPS;
		duty_cycle = amplitude - ramp_down_duty_cycle_step;
		motor_IN.write(duty_cycle);
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	currentTime = timer.read_us();
	if (currentTime - prevTime >= ramp_down_wait_interval) {
		// decrement PWM duty cycle
		prevTime = currentTime;
		duty_cycle -= ramp_down_duty_cycle_step;
		motor_IN.write(duty_cycle);
	}

	if (currentTime - phaseStartTime >= decay_time_us) {
		// end phase, set state to next phase
		currentState = stopped;
		ramp_down_phase_begin = true;
	}
}

/*
 * Function name: runMotor
 * Description: Keeps motor running at the set amplitude for on_time_us microseconds.
 * Arguments: N/A
 * Return value: N/A
 * Note: on_time_us can be set using the setOnTime_s method
 */
void MotorControl::runMotor() {
	// initialize phase variables
	// execute once at start of phase
	if (running_phase_begin) {
		running_phase_begin = false;
		duty_cycle = amplitude;
		motor_IN.write(duty_cycle);
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	currentTime = timer.read_us();
	if (currentTime - phaseStartTime >= on_time_us) {
		// end phase, set state to next phase
		currentState = rampDown;
		running_phase_begin = true;
	}
}

/*
 * Function name: stopMotor
 * Description: Stops motor for off_time_us microseconds.
 * Arguments: N/A
 * Return value: N/A
 * Note: off_time_us can be set using the setOffTime_s method
 */
void MotorControl::stopMotor() {
	// initialize phase variables
	// execute once at start of phase
	if (stopped_phase_begin) {
		stopped_phase_begin = false;
		duty_cycle = 0;
		motor_IN.write(duty_cycle);
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	currentTime = timer.read_us();
	if (currentTime - phaseStartTime >= off_time_us) {
		// end phase, set state to next phase
		stopped_phase_begin = true;
		if (repeat)
			currentState = rampUp;
		else
			currentState = off;
	}
}

/*
 * Function name: setRiseTime_s
 * Description: Sets the length of the ramp up phase
 * Arguments: time_s - time in seconds
 * Return value: N/A
 * Note: if time_s is negative, the length of the phase will be 0
 */
void MotorControl::setRiseTime_s(const float &time_s) {
	rise_time_us = seconds_to_microseconds(time_s);
}

/*
 * Function name: setDecayTime_s
 * Description: Sets the length of the ramp down phase
 * Arguments: time_s - time in seconds
 * Return value: N/A
 * Note: if time_s is negative, the length of the phase will be 0
 */
void MotorControl::setDecayTime_s(const float &time_s) {
	decay_time_us = seconds_to_microseconds(time_s);
}

/*
 * Function name: setOnTime_s
 * Description: Sets the length of the running phase
 * Arguments: time_s - time in seconds
 * Return value: N/A
 * Note: if time_s is negative, the length of the phase will be 0
 */
void MotorControl::setOnTime_s(const float &time_s) {
	on_time_us = seconds_to_microseconds(time_s);
}

/*
 * Function name: setOffTime_s
 * Description: Sets the length of the stopped phase
 * Arguments: time_s - time in seconds
 * Return value: N/A
 * Note: if time_s is negative, the length of the phase will be 0
 */
void MotorControl::setOffTime_s(const float &time_s) {
	off_time_us = seconds_to_microseconds(time_s);
}

void MotorControl::setRiseTime_us(const int &time_s){}
void MotorControl::setDecayTime_us(const int &time_s){}
void MotorControl::setOnTime_us(const int &time_s){}
void MotorControl::setOffTime_us(const int &time_s){}

/*
 * Function name: setAmplitude
 * Description: Sets the amplitude of the motor output 1.0 motor runs at maximum speed
 * Arguments: value - 
 * Return value: N/A
 */
void MotorControl::setAmplitude(const float &value) {
	if (value < 0)
	    amplitude = 0;
	else if (value > 1.0)
		amplitude = 1;
	else
		amplitude = value;
}

void MotorControl::setRepeat(const bool &value) {
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

// intitializes cycle. can be used to restart cycle from the beginning (rampUp)
void MotorControl::start() {
	currentState = rampUp;
	ramp_up_phase_begin = true;
	running_phase_begin = true;
	ramp_down_phase_begin = true;
	stopped_phase_begin = true;
}
