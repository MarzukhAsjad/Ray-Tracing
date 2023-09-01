#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

#include <iostream>

inline double linear_to_gamma(double linear_component) {
    return sqrt(linear_component);
}

// Calulate colour for multiple samples per pixel 
void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    // initalise the colour variables
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the colour by the number of samples (Initial step in introduce anti-aliasing)
    auto scale = 1.0 / samples_per_pixel;
    // Gamma correct for gamma = 2.0 to make colour more light
    r = linear_to_gamma(scale * r);
    g = linear_to_gamma(scale * g);
    b = linear_to_gamma(scale * b);

    // Write the translated [0,255] value of each color component.
    static const interval intensity(0.000, 0.999);
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif