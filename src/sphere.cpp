#include "../headers/sphere.h"

Sphere::Sphere(const vector3 &center, float radius) : Surface(center), radius(radius)  {}

bool Sphere::hit_ray(const Ray &ray, float t0, float t1, hit_record &rec)  {
    bool hit = false;

    // Equation of sphere
    // center C (a, b, c)
    // point P (x, y, z) = (ray.origin + ray.direction * t)
    // (x-a)^2 + (y-b)^2 + (z-c)^2 = r^2
    // (P-C) * (P-C) = r^2
    // (ray.origin + ray.direction * t - C) * (ray.origin + ray.direction * t - C) = r^2
    // (ray.direction * ray.direction) t^2  +   2 ray.direction * (ray.origin - C) t + (ray.origin - C) * (ray.origin - C) - r^2 = 0
    // At^2 + Bt + C
    // A = (ray.direction * ray.direction)
    // B = 2 ray.direction * (ray.origin - C)
    // C = (ray.origin - C) * (ray.origin - C) - r^2
    float A = ray.direction * ray.direction;
    float B = (ray.direction*2) * (ray.origin - this->origin);
    float C = (ray.origin - this->origin) * (ray.origin - this->origin) - this->radius * this->radius;
    
    // If discriminant < 0, no real solutions (ray misses sphere)
    float disc = B*B-4*A*C;
    float t;
    if (disc >= 0) {
        hit = true;
        // Solve quadratic equation for t
        float tplus = (-B + sqrt(disc))/(2*A);
        float tminus = (-B - sqrt(disc))/(2*A);
        float min, max;
        if (tplus <= tminus) {
            min = tplus;
            max = tminus;
        }
        else {
            max = tplus;
            min = tminus;
        }
        // Select the closest t that's in range (the first intersection)
        if (min >= t0 && min <= t1)
            t = min;
        else if (max >= t0 && min <= t1)
            t = max;
        else
            hit = false;
    }
    
    if (hit) {
        vector3 intersection = ray.origin + ray.direction * t;
        vector3 normal = (intersection - this->origin)/this->radius; // Normalized 
        rec = hit_record{t, normal};
    }
    else { // This should not be used, but is to ensure the hit-record gets data
        rec = hit_record{t1, ray.direction};
    }

    return hit;
}