#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "utility.h"
#include "interval.h"

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    shared_ptr<material> mat;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        // if dot product is positive, then ray and normal are opposite, meaning ray is coming from the outside
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
    public:
        virtual ~hittable() = default;
        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0; // = 0 means that any class that inherits from "hittable" must provide its own implementation of this method
};

#endif