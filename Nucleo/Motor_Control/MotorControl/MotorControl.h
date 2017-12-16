/*
 * MotorControl.cpp
 * Author: Davis Chen
 * Last Revised: 2017/12/15
 */

/* floats and seconds
 * may be better to use only ints and microseconds and let the calling program handle type conversions
 */

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "mbed.h"
#include "Timer.h"

class MotorControl {
	public:
		// length of 1 PWM cycle in microseconds
		static const int PWM_PERIOD_US = 1000;
		// number of steps to use when ramping up and ramping down
		static const int RAMP_STEPS = 10;

		enum State {rampUp, running, rampDown, stopped, off};

		MotorControl(PinName pin);
		MotorControl(PinName pin, float rise_time_us, float on_time_us, float decay_time_us, float off_time_us, float amplitude);

		void setRiseTime_s(const float &time_s);
		void setDecayTime_s(const float &time_s);
		void setOnTime_s(const float &time_s);
		void setOffTime_s(const float &time_s);

		void setRiseTime_us(const int &time_s);
		void setDecayTime_us(const int &time_s);
		void setOnTime_us(const int &time_s);
		void setOffTime_us(const int &time_s);

		void setAmplitude(const float &value);

		void setRepeat(const bool &value);

		void run();
		void start();

		float getAmplitude() {return amplitude;}
		float getMotorLevel() {return motor_level;}
	private:
		Timer timer;
		int prevTime;
		int currentTime;
		int phaseStartTime;

		PwmOut motor_IN;

		State currentState;
		bool repeat = true;

		// length of each phase in microseconds
		// each phase is set to 1 second by default
		int rise_time_us = 1000000;
		int on_time_us = 1000000;
		int decay_time_us = 1000000;
		int off_time_us = 1000000;

		// Amplitude as a
		float amplitude = 1.0;
		float motor_level;

		bool ramp_up_phase_begin = true;
		int ramp_up_wait_interval;
		float ramp_up_motor_level_step;

		bool ramp_down_phase_begin = true;
		int ramp_down_wait_interval;
		float ramp_down_motor_level_step;

		bool running_phase_begin = true;
		bool stopped_phase_begin = true;

		// Ramps up motor linearly until it reaches the set amplitude
		void rampUpMotor();

		// Stop motor by ramping down linearly from the set amplitude
		void rampDownMotor();

		void runMotor();
		void stopMotor();
};

#endif
