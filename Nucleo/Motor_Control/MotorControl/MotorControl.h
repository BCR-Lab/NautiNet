/*
 * MotorControl.h
 * Author: Davis Chen
 * Last Revised: 2017/12/30
 * Description: Header file for the MotorControl class
 */

/* Future work and Improvements:
 * may be better to use only microseconds for time values and let the calling program handle type conversions
 * This would require changing the constructor and setter methods
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
		static const int RAMP_STEPS = 100;

		enum State {rampUp, running, rampDown, stopped, off};

		MotorControl(PinName pin);
		MotorControl(PinName pin, float rise_time_s, float on_time_s, float decay_time_s, float off_time_s, float amplitude);

		void run();
		void start();

		// Setters and getters
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

		int getRiseTime_us() {return rise_time_us;}
		int getDecayTime_us() {return decay_time_us;}
		int getOnTime_us() {return on_time_us;}
		int getOffTime_us() {return off_time_us;}

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

		// Maximum amplitude of the cycle (valid values from 0 to 1.0)
		float amplitude = 1.0;
		float motor_level;

		bool phase_begin = true;
		int wait_interval; // time interval between steps
		float motor_level_step; // size of step when ramping up or down
		float motor_level_error; // used to avoid problems caused by floating point arithmetic

		int current_step; // keeps track of the current step

		// Ramps up motor linearly until it reaches the set amplitude
		void rampUpMotor();

		// Stop motor by ramping down linearly from the set amplitude
		void rampDownMotor();

		void runMotor();
		void stopMotor();
};

#endif
