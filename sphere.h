#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere() {}
        sphere(point3 cen, double r) : center(cen), radius(r) {};

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
            // calculates the terms in the equation
            vec3 oc = r.origin() - center;
            auto a = r.direction().length_squared();
            auto half_b = dot(oc, r.direction());
            auto c = oc.length_squared() - radius*radius;

            // calculates the discriminant
            auto discriminant = half_b*half_b - a*c;
            if (discriminant < 0) return false;
            auto sqrtd = sqrt(discriminant);

            // Find the nearest root that lies in the acceptable range.
            auto root = (-half_b - sqrtd) / a; // this is the root from the equation
            if (!ray_t.surrounds(root)) { // if out of range of valid time interval with negative discriminant
                root = (-half_b + sqrtd) / a; // then check positive discriminant
                if (!ray_t.surrounds(root)) // if still out range of valid interval, then discard root
                    return false;
            }

            // store the hit record if in valid interval
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }

    public:
        point3 center;
        double radius;
};

#endif