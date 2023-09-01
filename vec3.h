#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "utility.h"

using std::sqrt;

class vec3 {
    public:
        // Constructors
        vec3() : e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        // Publicly calling individual components, e.g. y_sq = v.y * v.y 
        // (assuming v already initialised as a vec3)
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // overloaded operators
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // Constant unary minus operator, returns vec with negative values
        double operator[](int i) const { return e[i]; } // Constant subscript operator (to read but can't be modified)
        double& operator[](int i) { return e[i]; } // Non constant subscript operator (to read AND modify)

        vec3& operator+=(const vec3 &v) { // Non constant reference of vec3 object (adding)
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(const double t) { // Non constant reference of vec3 object (scalar multiplying)
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t) { // Non constant reference of vec3 object (scalar dividing)
            return *this *= 1/t;
        }

        double length() const { // Length of vector (l)
            return sqrt(length_squared());
        }

        double length_squared() const { // Intermediary value (l^2)
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        // Return true if the vector is close to zero in all dimensions
        bool near_zero() const {
            auto s = 1e-8; // Small number close to 0
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }

        // Return a vec3 with random parameters in range [0, 1)
        static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        // Return a vec3 with random parameteres in range [min, max)
        static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

    public:
        double e[3]; // For storing the x, y and z components
};

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color



// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

// Pick a random point in unit sphere where all parameters of the point (x,y,z) are in [-1, +1]
inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue; // If not within sphere
        return p;
    }
}

// normalises the unit sphere by making a unit vector of it
vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

// Pick a random point in unit hemisphere...
vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

// Computes the reflection vector of the incident vector off the surface
vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

#endif