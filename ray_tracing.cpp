#include "utility.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include <iostream>


// Checks if the sphere is hit by the input ray
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared(); 
    auto half_b = dot(oc, r.direction()); // Replacing b by 2h in the roots of equation
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) { // If no intersection
        return -1.0;
    } 
    else { // Otherwise intersection happened.
        return (-half_b - sqrt(discriminant) ) / a;
    }
}

// Creates a colour object output from an input ray object
color ray_color(const ray& r, const hittable& world, int depth) { // Depth added to control recursion
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light will be gathered
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0, infinity, rec)) {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1); // Recursively generate rays
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5)); // The sphere
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100)); // The ground (a large sphere)

    // Camera
    camera cam;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0); // initialise a pixel colour
            // for each of the pixel, send ray, obtain colour output, and then calculate av. colour for each pixel
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
