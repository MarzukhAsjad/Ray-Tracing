#ifndef CAMERA_H
#define CAMERA_H

#include "utility.h"

class camera {
    public:
        camera() {
            // Some initial double variables for calculation of screen
            auto aspect_ratio = 16.0 / 9.0;
            auto viewport_height = 2.0;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1.0; // Distance between projection plane and projection point

            origin = point3(0, 0, 0); // This can be considered as the eye/camera
            horizontal = vec3(viewport_width, 0.0, 0.0); // Horizontal dimension of the viewport in worldspace
            vertical = vec3(0.0, viewport_height, 0.0); // Vertical dimension of the viewport in worldspace
            lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
        }

        // Shoot ray from point in camera (for rendering)
        ray get_ray(double u, double v) const {
            return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};
#endif