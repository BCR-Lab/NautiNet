/*
 * MotorControl.cpp
 * Author: Davis Chen
 * Last Revised: 2017/12/15
 *
 * Description: This class is used to control the motor in a nautilus robot.
 * The motor is ramped up to a specfic speed, stays at that speed for a short while,
 * and ramps back down. After a short delay, the cycle begins again.
 * All parameters can be set by the calling program.
 */

#include "MotorControl.h"

/*
 * Function name: seconds_to_microseconds
 * Description: Converts an amount of time from seconds to microseconds
 * Arguments: n - the amount of time to be converted in seconds
 * Return value: returns the amount of time in microseconds; 0 will be returned if input value is negative
 */
static int seconds_to_microseconds(const float &n) {
	if (n < 0)
		return 0;
	// 1 million microseconds in a second
	return n*1000000;
}

/*
 * Function name: class constructor
 * Description: class constructor
 * Arguments: pin - the name of the output pin (use only PWM capable pins)
 * Return value: N/A
 */
MotorControl::MotorControl(PinName pin) : motor_IN(pin){
	// start internal timer
	timer.start();
	// set PWM frequency
	motor_IN.period_us(PWM_PERIOD_US);
}

/*
 * Function name: class constructor
 * Description: initializes variables with the input parameters
 * Arguments: pin - the name of the output pin (use only PWM capable pins)
 *            rise_time_s - the rise time in seconds
 *            on_time_s - the on time in seconds
 *            decay_time_s - the decay time in seconds
 *            off_time_s - the off time in seconds
 *            amplitude - the amplitude (maximum speed of motor)
 *                        should be a value between 0 and 1 where 0 is off and 1 is full speed
 * Return value: N/A
 */
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
 * Function name: calculateDutyCycle
 * Description: Converts the desired motor level to the appropriate duty cycle for the DRV8871 motor driver
 * Arguments: motor_level - the desired motor level
 * Return value: The corresponding duty cycle for the motor level
 */
static float calculateDutyCycle(float motor_level) {
	return 1 - motor_level;
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
		ramp_up_motor_level_step = amplitude/RAMP_STEPS;
		motor_level = 0;
		motor_IN.write(calculateDutyCycle(motor_level));
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	currentTime = timer.read_us();
	if (motor_level >= amplitude) {
		// end phase, set state to next phase
		currentState = running;
		ramp_up_phase_begin = true;
		printf("%d\n", currentTime-phaseStartTime);
		return;
	}

	if (currentTime - prevTime >= ramp_up_wait_interval) {
		// increment PWM duty cycle
		prevTime = currentTime;
		motor_level += ramp_up_motor_level_step;
		motor_IN.write(calculateDutyCycle(motor_level));
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
		ramp_down_motor_level_step = amplitude/RAMP_STEPS;
		motor_level = amplitude;
		motor_IN.write(calculateDutyCycle(motor_level));
		prevTime = timer.read_us();
		phaseStartTime = prevTime;
	}

	currentTime = timer.read_us();

	if (motor_level <= 0) {
		// end phase, set state to next phase
		currentState = stopped;
		ramp_down_phase_begin = true;
		return;
	}
	if (currentTime - prevTime >= ramp_down_wait_interval) {
		// decrement PWM duty cycle
		prevTime = currentTime;
		motor_level -= ramp_down_motor_level_step;
		motor_IN.write(calculateDutyCycle(motor_level));
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
		motor_level = amplitude;
		motor_IN.write(calculateDutyCycle(motor_level));
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
		motor_level = 0;
		motor_IN.write(calculateDutyCycle(motor_level));
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
 * Description: Sets the maximum speed the motor output
 * Arguments: value - valid values are between from 0 to 1, where 0 is off and 1 is full speed
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

/*
 * Function name: setRepeat
 * Description: Used to set the repeat variable
 * Arguments: value - the value to set repeat to; set to true to repeat the cycle at the end of a cycle
 * Return value: N/A
 */
void MotorControl::setRepeat(const bool &value) {
	repeat = value;
}

/*
 * Function name: run
 * Description: This function must be called continuouly to run the motor.
 *              The current state (phase of the cycle) is checked and the appropriate function is called.
 * Arguments: N/A
 * Return value: N/A
 */
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

/*
 * Function name: start()
 * Description: Initializes some variables to begin a new cycle
 *              Can be used to restart the cycle from the beginning
 * Arguments: N/A
 * Return value: N/A
 */
void MotorControl::start() {
	currentState = rampUp;
	ramp_up_phase_begin = true;
	running_phase_begin = true;
	ramp_down_phase_begin = true;
	stopped_phase_begin = true;
}
