#ifndef PITOT_TUBE_H
#define PITOT_TUBE_H

/**
 * @brief Simulates a Pitot tube.
 *
 * A Pitot tube is a device used to measure the velocity of a fluid. It uses Bernoulli's Principle to calculate the
 * dynamic pressure of a fluid by measuring the difference between the static pressure and the stagnation (total)
 * pressure. This difference in presesure \f$\Delta p\f$ can be measured using a pressure transducer. Then, given the
 * density of the fluid \f$\rho\f$, the velocity of the fluid \f$v\f$ can be calculated using:
 *
 * \f[v = \sqrt{\frac{2\Delta p}{\rho}}\f]
 *
 * @param true_pressure_difference The true pressure difference that is to be measured by the pressure transducer in
 * \f$Pa\f$.
 * @param fluid_density The density of the fluid in \f$kgm^{-3}\f$.
 *
 * @return The uncertain velocity of the fluid in \f$ms^{-1}\f$ after adding measurement uncertainty of the pressure
 * transducer.
 */
double pitot_tube(double true_pressure_difference, double fluid_density);

#endif