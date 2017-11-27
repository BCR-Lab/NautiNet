/*
 * Davis Chen
 */

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "mbed.h"
#include "Timer.h"

class MotorControl {
	public:

		MotorControl(PinName pin1, PinName pin2);
		MotorControl(PinName pin1, PinName pin2, float rise_time_us, float on_time_us, float decay_time_us, float off_time_us, float amplitude);

		void setRampUpTime_s(float time_s);
		void setRampDownTime_s(float time_s);
		void setOnTime_s(float time_s);
		void setOffTime_s(float time_s);

		void setAmplitude(float value);

		void setRepeat();

		void run();

	private:
		Timer timer;
		int prevTime;

		PwmOut motor_IN1;
		PwmOut motor_IN2;

		enum State {rampUp, running, rampDown, stopped, off};
		State currentState;
		bool repeat = true;

		// length of 1 PWM cycle (in seconds)
		static const float PWM_PERIOD = 0.001;
		static const int RAMP_STEPS = 100;

		// length of each phase in microseconds
		int rise_time_us = 1000000;
		int on_time_us = 1000000;
		int decay_time_us = 1000000;
		int off_time_us = 1000000;

		float amplitude = 1.0;

		int phaseStartTime;

		// Ramps up motor linearly until it reaches the set amplitude
		void rampUp();

		// Stop motor by ramping down linearly from the set amplitude
		void rampDown();

		void runMotor();
		void stopMotor();
};

#endif
