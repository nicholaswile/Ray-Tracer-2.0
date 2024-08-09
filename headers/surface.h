#pragma once

#include "nikomath.h"
#include "material.h"

struct hit_record {
    float t;
    vector3 normal;
    Material *mat;
};

class Surface {
public:

    virtual bool hit_ray(const Ray &ray, float t0, float t1, hit_record &rec) const = 0;
    Surface();
    Material *material;

    // TODO: bounding box
};