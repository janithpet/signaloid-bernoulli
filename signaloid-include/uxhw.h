#ifndef UXHW_H
#define UXHW_H

#include <stddef.h>

/**
 * @brief Simulates the <a href="https://docs.signaloid.io/docs/hardware-api/inserting-uncertainty/dist-from-samples/">UxHwDoubleDistFromSamples from the Signaloid UxHw Hardware API</a>.
 *
 * @param samples An array of samples from the underlying distribution.
 * @param sampleCount The number of samples. I.e the length of the `samples` array .
 *
 * @return Currently returns average of the samples.
 */
double UxHwDoubleDistFromSamples(double* samples, size_t sampleCount);

/**
 * @brief Simulates the <a href="https://docs.signaloid.io/docs/hardware-api/inserting-uncertainty/parametric-distributions/uniform-dist/">UxHwDoubleUniformDist from the Signaloid UxHw Hardware API</a>.
 *
 * @param min The minimum value of the distribution.
 * @param max The maximum value of the distribution.
 *
 * @return The average of the min and max.
 */
double UxHwDoubleUniformDist(double min, double max);

/**
 * @brief Simulates the <a href="https://docs.signaloid.io/docs/hardware-api/inserting-uncertainty/parametric-distributions/gauss-dist/">UxHwDoubleGaussDist from the Signaloid UxHw Hardware API</a>.
 *
 * @param mean The mean of the distribution.
 * @param stddev The standard deviation of the distribution.
 *
 * @return The mean.
 */
double UxHwDoubleGaussDist(double mean, double stddev);

#endif