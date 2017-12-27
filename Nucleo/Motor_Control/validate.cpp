/*
 * Davis Chen
 */

#include "mbed.h"
#include "MotorControl.h"
#include "Timer.h"

Serial pc(SERIAL_TX, SERIAL_RX);

int main() {
	pc.baud(57600);
	Timer t;
	t.start();

	float rise = 0.01, running = 0.01, decay = 0.01, wait = 0.01;
	float amplitude = 1.0;
	const int cycles = 100;
	const int samples_per_phase = 2;
	int period = (rise + running + decay + wait) * 1000000 * cycles;
	MotorControl m(D3, rise, running, decay, wait, amplitude);
	//m.setRepeat(false);

	// Need to disable repeat and manually restart with start() after every cycle because printing to serial is very slow and would cause timing issues

	int prev_time, current_time, start_time;
	const int sample_count = cycles * samples_per_phase * 4;
	int sample_interval = period / (sample_count);

	/*
	float times[4] = {0.001, 0.01, 0.1, 1};

	for (int i=0; i<4; i++) {
		int test_time = times[i]*110*1000000;
		m.setRiseTime_s(times[i]);
		printf("Rise time: %0.2f\n", times[i]);
		printf("Amplitude: %0.2f\n", amplitude);
		start_time = t.read_us();
		current_time = start_time;
		m.start();
		while (current_time - start_time < test_time) {
			m.run();
			current_time = t.read_us();
		}
	}
	*/
	printf("Rise time: %0.2f On time: %0.2f Decay time: %0.2f Off time: %0.2f\n", rise, running, decay, wait);
	printf("Amplitude: %0.2f\n", amplitude);

	struct t_data {
		int time;
		float level;
	};

	for (int j=0; j< 1; j++) {
		int i=0;
		float a[sample_count];
		prev_time = t.read_us();
		start_time = prev_time;
		m.start();
		while (i < sample_count) {
			m.run();
			current_time = t.read_us();
			if (current_time - start_time >= sample_interval*(1+i)) {
				a[i] = m.getMotorLevel();
				//prev_time = current_time;
				i++;
			}
		}
		current_time = t.read_us();

		//printf("Time taken: %d\n", current_time - start_time);
		// print values from cycle
		for (int k=0; k < sample_count; k++)
			printf("%0.2f\t", a[k]);
		printf("\n");
	}

	printf("complete\n");
}
