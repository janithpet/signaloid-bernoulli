#include "uxhw.h"

#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

double UxHwDoubleDistFromSamples(double* samples, size_t samplesCount) {
	double sum = 0;
	for (int i = 0; i < samplesCount; i++) {
		sum += samples[i];
	}
	return sum / samplesCount;
}

double UxHwDoubleUniformDist(double min, double max) {
	return (max + min) / 2;
}

double UxHwDoubleGaussDist(double mean, double stddev) {
	return mean;
}
