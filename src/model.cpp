#include "model.h"

Model::Model(double t) {
	srand(time(NULL));

	lastTime = t;

	ambientTemp = 298.f; // 25C
	
	loadTemp = 283.f; // 10C
	loadCapacity = 4.18f; // Specific heat of water J/gºC
	load = 1000.f; // 1 liter of water (1kg)
	/**
	(k/s) * A
	k = 30 W/mK (stainless steel)
	s = 0.01m (1cm thick)
	A = 0.5m*0.5m = 0.25m^2
	*/
	Ula = 75.f; // W/K

	plateTemp = ambientTemp; // Plate is at ambient
	plateCapacity = 0.385f; // Copper
	plate = 896.f; // 10cm * 10cm * 1cm thick copper
	Upa = 15.f;

	plateAmps = 0.f;
	plateVoltage = 120.f;
	plateAmpsPerSec = 8.f;
	plateMaxAmps = 50.f;

	Ulp = 50.f; // Made up number cause I dont know how to do this
}

void Model::update(double t) {
	double dt = t - lastTime;

	// Randomly changes the load
	if (rand() % 100 == 0) {
		load = (double)(rand() % 1750) + 250.f; // Randomly 250ml to 2L
		// loadCapacity = (double)((rand() % 4000) + 1000) / 1000.f;
		loadTemp = (double)((rand() % 50) + 283); // Randomly 10 to 60C
	}

	// Number of watts transfered (J/s)
	double Qla = (ambientTemp - loadTemp) * Ula;
	double Pla = Qla*dt; // Number of J transfered
	loadTemp += Pla / (loadCapacity * load);

	double C = plateAmps * dt;
	double J = C * plateVoltage;
	plateTemp += J / (plateCapacity * plate);

	double Qpa = (ambientTemp - plateTemp) * Upa;
	double Ppa = Qpa*dt;
	plateTemp += Ppa / (plateCapacity * plate);

	double Qlp = (plateTemp - loadTemp) * Ulp;
	double Plp = Qlp*dt;
	loadTemp += Plp / (loadCapacity * load);
	plateTemp -= Plp / (plateCapacity * plate);

	lastTime = t;
}

double Model::getLoadTemp() {
	return loadTemp;
}


double Model::getPlateTemp() {
	return plateTemp;
}

double Model::getAmbientTemp() {
	return ambientTemp;
}

double Model::getAmps() {
	return plateAmps;
}

void Model::setAmps(double a, double dt) {	
	double sa = a;
	if (a > plateMaxAmps) {
		sa = plateMaxAmps;
	} else if (a < 0.f) {
		sa = 0.f;
	}

	double da = sa - plateAmps;
	double sign = da / std::abs(da);

	if (std::abs(da) < plateAmpsPerSec*dt) {
		plateAmps = sa;
	} else {
		plateAmps += sign * plateAmpsPerSec * dt;
	}
}