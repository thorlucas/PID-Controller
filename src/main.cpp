#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "pid.h"
#include "model.h"

int main(int argc, char *argv[]) {
	double kp = 1.f;
	double ki = 0.f;
	double kd = 0.f;

	int c;
	while ( (c = getopt(argc, argv, "p:i:d:")) != -1) {
		switch(c) {
			case 'p':
				kp = atof(optarg);
				break;
			case 'i':
				ki = atof(optarg);
				break;
			case 'd':
				kd = atof(optarg);
				break;
			default:
				break;
		}
	}


	Model m(0);
	PIDController pid(323, m.getLoadTemp(), 0, kp, ki, kd);

	std::cout << "# Time\tLoad\tSet Point\tPlate Amps\n";

	for (double t = 1; t < 600; t += 1) {
		m.update(t);
		double c = pid.output(t, m.getLoadTemp());
		m.setAmps(c, 1);
		std::cout << t << "\t" << m.getLoadTemp() << "\t" << "323" << "\t" << m.getAmps() << "\n";
	}

	return 0;
}