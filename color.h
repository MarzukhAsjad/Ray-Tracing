#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

// Calulate colour for multiple samples per pixel 
void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    // initalise the colour variables
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the colour by the number of samples (Initial step in introduce anti-aliasing)
    auto scale = 1.0 / samples_per_pixel;
    // Gamma correct for gamma = 2.0 to make colour more light
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif