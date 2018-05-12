#include "pid.h"

PIDController::PIDController(double sp, double pv, double t, double p, double i, double d) : 
	setpoint(sp), lastTime(t), Kp(p), Ki(i), Kd(d) {
	integral = 0.f;
	lastError = error(pv);
}

double PIDController::output(double t, double pv) {
	double dt = t-lastTime;
	double e = error(pv);

	integral += dt*e;
	derivative = (e-lastError)/dt;

	double o =  Kp*e + Ki*integral + Kd*derivative;

	lastError = e;
	lastTime = t;
	return o;
}

double PIDController::error(double pv) {
	return setpoint - pv;
}