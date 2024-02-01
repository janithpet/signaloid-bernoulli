#include <math.h>
#include <stdio.h>

#include "pitot-tube.h"

const double AIR_DENSITY                = 1.225;
const double TOP_PRESSURE_DIFFERENCE    = 1825.4386486517;
const double BOTTOM_PRESSURE_DIFFERENCE = 440.3715965603;

/**
 * @brief Simulates the measurement of the velocity of air on the top of an airfoil in \f$ms^{-1}\f$ through a pitot
 * tube.
 *
 *
 * @return An uncertain measurement of the velocity of the air on the top of the
 * airfoil.
 */
double measure_velocity_top(void) { return pitot_tube(TOP_PRESSURE_DIFFERENCE, AIR_DENSITY); }

/**
 * @brief Simulates the measurement of the velocity of air on the bottom of an airfoil in \f$ms^{-1}\f$ through a pitot
 * tube.
 *
 * @return An uncertain measurement of the velocity of the air on the bottom of the airfoil.
 */
double measure_velocity_bottom(void) { return pitot_tube(BOTTOM_PRESSURE_DIFFERENCE, AIR_DENSITY); }

/**
 * @brief Simulates the measurement of the surface area of the airfoil in
 * \f$m^{2}\f$.
 *
 * @return A measurement of the surface area of the airfoil.
 */
double measure_airfoil_area(void) { return 1.0; }

/**
 * @brief Calculates the lift of an airfoil using Bernoulli's Principle.
 *
 * The lift of an airfoil can by estimated by using Bernoulli's Principle. By measuring the velocity of air on the top
 * \f$v_t\f$ and bottom \f$v_b\f$ of the airfoil, the density of air \f$\rho\f$, and the surface area of the airfoil
 * \f$A\f$, the lift \f$L\f$ can be calculated using:
 *
 * \f[L = \frac{1}{2} \rho A(v_t^2 - v_b^2)\f]
 *
 * @param velocity_top The velocity of the air on the top of the airfoil in
 * \f$ms^{-1}\f$.
 * @param velocity_bottom The velocity of the air on the bottom of the airfoil
 * in \f$ms^{-1}\f$.
 * @param air_density The density of the air in \f$kgm^{-3}\f$.
 * @param area The area of the airfoil in $\f$m^{2}\f$.
 * @return The lift of the airfoil in \f$N\f$.
 */
double calculate_lift(double velocity_top, double velocity_bottom, double air_density, double area) {
	return 0.5 * air_density * area * (pow(velocity_top, 2) - pow(velocity_bottom, 2));
}

int main(void) {
	double velocity_top    = measure_velocity_top();
	double velocity_bottom = measure_velocity_bottom();
	double air_density     = measure_airfoil_area();
	double area            = measure_airfoil_area();

	double lift            = calculate_lift(velocity_top, velocity_bottom, air_density, area);

	printf("The lift of the airfoil is %fN.\n", lift);
	return 0;
}