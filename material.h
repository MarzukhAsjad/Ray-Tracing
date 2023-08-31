#ifndef MATERIAL_H
#define MATERIAL_H

#include "utility.h"

struct hit_record;

// abstract class
class material {
    public:
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const = 0;
};

#endif