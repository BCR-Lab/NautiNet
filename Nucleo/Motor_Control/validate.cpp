/*
 * Davis Chen
 */

#include "mbed.h"
#include "MotorControl.h"
#include "Timer.h"

Serial pc(SERIAL_TX, SERIAL_RX);

int main() {
	pc.baud(57600); // set to higher baud rate for faster transmit times
	Timer t;
	t.start();

	float rise = 0.01, running = 0.01, decay = 0.01, wait_t = 0.01;
	float amplitude = 1.0;
	const int cycles = 100;
	const int samples_per_phase = 2;
	int period = (rise + running + decay + wait_t) * 1000000 * cycles;
	MotorControl motor(D3, rise, running, decay, wait_t, amplitude);

	// Only a limited amount of data can be stored due to limited memory on the microcontroller. Datamust be printed out before collecting more data.
	// Need to manually restart with start() after printing because printing to serial is very slow and would cause timing issues with future measurements

	int current_time, start_time;
	const int sample_count = cycles * samples_per_phase * 4; // total number of measurments
	int sample_interval = period / (sample_count); // time between measurements
	float data[sample_count];

	printf("Rise time: %0.2f On time: %0.2f Decay time: %0.2f Off time: %0.2f\n", rise, running, decay, wait_t);
	printf("Amplitude: %0.2f\n", amplitude);

	for (int j=0; j< 10; j++) {
		int i=0;
		start_time = t.read_us() - 40; // offset measurement times to measure between value changes
		motor.start();
		while (i < sample_count) {
			motor.run();
			current_time = t.read_us();
			if (current_time - start_time >= sample_interval*(1+i)) {
				// take measurement
				data[i] = motor.getMotorLevel();
				i++;
			}
		}

		// print collected measurements
		for (int k=0; k < sample_count; k++)
			printf("%0.2f\t", data[k]);
		printf("\n");
	}

	printf("complete\n");
}
