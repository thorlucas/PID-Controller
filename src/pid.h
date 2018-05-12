#ifndef _PID_H
#define _PID_H

/** Proportional, Integral, Derivative controller for feedback control loops
 *  This class has methods for computing the output, as well as the error
 *  and holding the different constants. Kp*e(t) + Ki*(integral 0->t e(t)) dt + Kd*(d/dx e(t))
 */
class PIDController {
private:
	double Kp; /**< Constant of proportionality. Multiplied directly to error. */
	double Ki; /**< Constant of integration. Multiplied to definite integral of the error. */
	double Kd; /**< Constant of differentiation. Multiplied to the derivative of the error. */

	double setpoint; /**< The set point we're trying to reach and maintain. */
	// double process; /**< The process variable. This is the current y(t). */

	double integral; /**< This is the cummulative integral. */
	double derivative; /**< This is the current derivative. */

	double lastTime; /**< The last time recorded. */
	double lastError; /**< The last error recorded. */
public:
	/** Sets up the controller.
	 *  @param sp the initial set point.
	 *  @param pv the initial process variable y(x).
	 *  @param t the initial time (usually 0).
	 */
	PIDController(double sp, double pv, double t = 0.f, double p = 1.f, double i = 1.f, double d = 1.f);

	/** Calculate the output we need to impart. Calculated by 
	 *  Kp*e(t) + Ki*(integral 0->t e(t)) dt + Kd*(d/dx e(t)).
	 *  @param t the time this process variable was recorded.
	 *  @param pv the process variable. (Current y(x)).
	 *  @returns the movement needed to impart.
	 */
	double output(double t, double pv);

	/** Calculate the error given the time and process variable.
	 *  @param pv the process variable. (Current y(x)).
	 *  @returns the error.
	 */
	double error(double pv);
};

#endif // _PID_H