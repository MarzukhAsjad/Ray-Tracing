#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "interval.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

// create a class of objects that are hittable
class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittable_list() {} // default constructor
        // we use shared_ptr since multible objects can reference to one single property (different spheres having the same texture)
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        // return true if ray intersected with any objects in the vector array
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_t.max;

            for (const auto& object : objects) {
                if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }        
};

#endif