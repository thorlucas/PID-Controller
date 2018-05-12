#ifndef _MODEL_H
#define _MODEL_H

#include <iostream>
#include <cstdlib>
#include "pid.h"
#include <time.h>
#include <cmath>

/** This is a simple model for heating of a load
 *  on a hotplate or something similar.
 *  The load loses heat to the ambient, as does
 *  the hotplate itself. Load temp often fluctuates
 *  suddenly when new liquid is added.
 */
class Model {
private:
	double ambientTemp; /**< The current ambient temperature. */
	double loadTemp; /**< The current load temperature. */
	double plateTemp; /**< The current temperature of the hotplate. */

	double loadCapacity; /**< The heat capacity of the load. J/K. */
	double plateCapacity; /**< The heat capacity of the plate. J/K. */

	double Upa; /**< Transfer coefficient between plate and ambient. */
	double Ula; /**< Transfer coefficient between load and ambient. */
	double Ulp; /**< Transfer coefficient between plate and load. */

	double load; /**< Load in grams */
	double plate; /**< Plate in grams */

	double plateAmps;
	double plateVoltage;
	double plateMaxAmps;
	double plateAmpsPerSec; /**< Maximum change of amps per second. */

	double lastTime;
public:
	Model(double t);
	void update(double t);
	double getLoadTemp();
	double getPlateTemp();
	double getAmbientTemp();
	double getAmps();

	void setAmps(double a, double t);
};

#endif // _MODEL_H