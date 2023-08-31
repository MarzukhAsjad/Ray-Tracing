#ifndef UTILITY_H
#define UTILITY_H

#include "interval.h"
#include "ray.h"
#include "vec3.h"

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

// Converts degrees to radians
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Returns a random real double in [0, 1)
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0); // Initialises a distribution in [0, 1)
    static std::mt19937 generator; // Initialises a Mersenne Twister pseudo-random number generator
    return distribution(generator); // Passes the generator into the distribution to return a number in that range
}

// Returns a random real double in [min, max)
inline double random_double(double min, double max) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

// Clamps the value within the range [min, max]
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Common Headers

#include "ray.h"
#include "vec3.h"

#endif