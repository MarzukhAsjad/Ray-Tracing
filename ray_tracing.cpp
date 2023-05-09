#include "color.h"
#include "vec3.h"
#include "ray.h"
#include <iostream>

// checks if the sphere is hit by the input ray
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) { // if no intersection
        return -1.0;
    } 
    else { // otherwise intersection happened.
        return (-b - sqrt(discriminant) ) / (2.0*a);
    }
}

// creates a colour object output from an input ray object
color ray_color(const ray& r) {
    auto t = hit_sphere(point3(0,0,-1), 0.5, r); // generate t values depending on sphere intersection with ray
    // colour for sphere (takes into account of depth/height)
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1)); // position vector of surface point
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1); // colouring based on depth of surface point from origin
    }
    // colour for everythng else (background)
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0); // smaller t corresponds to white and larger t corresponds to blue.
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0); // create a blend (smoothing lerp) between white and blue for the background
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0; // distance between projection plane and projection point

    auto origin = point3(0, 0, 0); // eye/camera
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1); // normalised horizontal distance between left edge and current pixel
            auto v = double(j) / (image_height-1); // normalised vertical distance between the bottom edge and current pixel
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin); // creating position vector for current pixel and then creating a ray object
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
