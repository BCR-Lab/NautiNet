/*
 * Davis Chen
 */

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "mbed.h"
#include "Timer.h"

class MotorControl {
	private:
		Timer timer;
		int prevTime;

		PwmOut motor_IN1;
		PwmOut motor_IN2;

		enum State {rampUp, running, rampDown, stopped, off};
		State currentState;
		State prevState;
		bool repeat = true;

		// length of 1 PWM cycle (in seconds)
		const float PWM_PERIOD = 0.001;
		const int RAMP_STEPS = 100;

		float rise_time = 1.0;
		float on_time = 1.0;
		float decay_time = 1.0;
		float off_time = 1.0;

		float amplitude = 1.0;

		int phaseStartTime;

	public:

		MotorControl(PinName pin1, PinName pin2);
		MotorControl(PinName pin1, PinName pin2, float rise_time, float on_time, float decay_time, float off_time, float amplitude);

		// Ramps up motor linearly until it reaches the desired amplitude
		void rampUp();

		// Stop motor by ramping down linearly
		void rampDown();

		void runMotor();
		void stopMotor();

		void setRampUpTime(float value);
		void setRampDownTime(float value);
		void setOnTime(float value);
		void setOffTime(float value);

		void setAmplitude(float value);

		void run();
};

#endif
