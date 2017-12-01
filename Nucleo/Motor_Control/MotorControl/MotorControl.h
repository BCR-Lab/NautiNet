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

		void setRampUpTime_s(float &time_s);
		void setRampDownTime_s(float &time_s);
		void setOnTime_s(float &time_s);
		void setOffTime_s(float &time_s);

		void setAmplitude(float &value);

		void setRepeat(bool value);

		void run();
		void start();

	private:
		Timer timer;
		int prevTime;

		PwmOut motor_IN1;
		PwmOut motor_IN2;

		enum State {rampUp, running, rampDown, stopped, off};
		State currentState;
		bool repeat = true;

		// length of 1 PWM cycle (in seconds)
		static const int PWM_PERIOD_US = 1000;
		static const int RAMP_STEPS = 100;

		// length of each phase in microseconds
		// each phase is set to 1 second by default
		int rise_time_us = 1000000;
		int on_time_us = 1000000;
		int decay_time_us = 1000000;
		int off_time_us = 1000000;

		// Amplitude as a
		float amplitude = 1.0;

		bool ramp_up_phase_start = true;
		int ramp_up_wait_interval;
		float ramp_up_duty_cycle_step;
		float ramp_up_duty_cycle;

		bool ramp_down_phase_start = true;
		int ramp_down_wait_interval;
		float ramp_down_duty_cycle_step;
		float ramp_down_duty_cycle;

		bool running_phase_start = true;
		bool stopped_phase_start = true;


		int phaseStartTime;

		// Ramps up motor linearly until it reaches the set amplitude
		void rampUpMotor();

		// Stop motor by ramping down linearly from the set amplitude
		void rampDownMotor();

		void runMotor();
		void stopMotor();
};

#endif
