#include "utility.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
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
color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
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

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5)); // The sphere
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100)); // The ground (a large sphere)

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0; // Distance between projection plane and projection point

    auto origin = point3(0, 0, 0); // This can be considered as the eye/camera
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1); // Normalised horizontal distance between left edge and current pixel
            auto v = double(j) / (image_height-1); // Normalised vertical distance between the bottom edge and current pixel
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin); // Creating position vector for current pixel and then creating a ray object
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
