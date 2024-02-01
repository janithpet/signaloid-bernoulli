#include <math.h>
#include <uxhw.h>

#include "pitot-tube.h"

const double PITOT_TUBE_RANGE_MAX        = 3650.0;    // Pa
const double PITOT_TUBE_RANGE_MIN        = 0.0;       // Pa
const double PITOT_TUBE_ERROR_FULL_SCALE = 0.5 / 100; // of full scale

double pitot_tube(double true_pressure_difference, double fluid_density) {
	// This function add uniform noises equal to \f$\pm 0.5\%\f$ of full scale to the true pressure difference.
	double error = PITOT_TUBE_ERROR_FULL_SCALE * (PITOT_TUBE_RANGE_MAX - PITOT_TUBE_RANGE_MIN);

	double uncertain_pressure_difference =
			UxHwDoubleUniformDist(true_pressure_difference - error, true_pressure_difference + error);

	return sqrt((2 * uncertain_pressure_difference) / fluid_density);
}