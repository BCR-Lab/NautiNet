/*
 * Davis Chen
 */

#include "mbed.h"
#include "MotorControl.h"
#include "Timer.h"

Timer t;
Serial pc(SERIAL_TX, SERIAL_RX);

int main() {
	pc.baud(57600);
	t.start();

	float rise = 0.005, running = 0.005, decay = 0.005, wait = 0.005;
	float amplitude = 1.0;
	int period = (rise + running + decay + wait) * 1000000;
	MotorControl m(D3, rise, running, decay, wait, amplitude);

	int prev_time, current_time;
	const int sample_count = 8;
	int sample_interval = period / (sample_count);

	printf("Rise time: %0.2f On time: %0.2f Decay time: %0.2f Off time: %0.2f\n", rise, running, decay, wait);
	printf("Amplitude: %0.2f\n", amplitude);
	for (int j=0; j<10000; j++) {
		int i=0;
		float a[sample_count];
		m.start();
		/*
		m.run();
		a[i] = m.getDutyCycle();
		i = 1;
		*/
		prev_time = t.read_us();
		while (i < sample_count) {
			m.run();
			current_time = t.read_us();
			if (current_time - prev_time >= sample_interval) {
				a[i] = m.getDutyCycle();
				prev_time = current_time;
				i++;
			}
		}
		
		// print values from cycle
		for (int k=0; k < sample_count; k++)
			printf("%0.2f\t", a[k]);
		printf("\n");
	}

	printf("complete\n");
}
