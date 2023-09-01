#include "utility.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include <iostream>

// Creates a colour object output from an input ray object
color ray_color(const ray& r, const hittable& world, int depth) { // Depth added to control recursion
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light will be gathered
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, interval(0.001, infinity), rec)) { // Ignoring hits near 0 (Decreasing tolerance) Fixes shadow acne problem
        point3 target = rec.p + rec.normal + random_in_hemisphere(rec.normal);
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1); // Recursively generate rays
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

    // World
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0)); // Material for the ground
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3)); // Material for the center sphere
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3); // Material for the metal sphere on the left
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0); // Material for the metal sphere on the right

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground)); // Sphere for the ground
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center)); // Center sphere
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left)); // Left sphere
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right)); // Right sphere

    // Camera and properties
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.reflectivity = 0.5;
    // Render
    cam.render(world);
}
