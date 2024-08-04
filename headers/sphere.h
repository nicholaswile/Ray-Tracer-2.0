#pragma once

#include "surface.h"

class Sphere : public Surface {
public:
    float radius;
    Sphere(const vector3 &center, float radius);
    bool hit_ray(const Ray &ray, float t0, float t1, hit_record &rec) override;
};