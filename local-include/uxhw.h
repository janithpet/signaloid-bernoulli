#ifndef UXHW_H
#define UXHW_H

#include <stddef.h>

/**
 * @brief Simulates the <a
 * href="https://docs.signaloid.io/docs/hardware-api/inserting-uncertainty/parametric-distributions/uniform-dist/">UxHwDoubleUniformDist
 * from the Signaloid UxHw Hardware API</a>.
 *
 * @param min The minimum value of the distribution.
 * @param max The maximum value of the distribution.
 *
 * @return The average of the min and max.
 */
double UxHwDoubleUniformDist(double min, double max);
#endif