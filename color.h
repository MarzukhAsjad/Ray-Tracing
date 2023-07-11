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
    r *= scale;
    g *= scale;
    b *= scale;
    
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif