#pragma once

#include "nikomath.h"
#include "material.h"

struct hit_record {
    float t;
    vector3 normal;
};

class Surface {
public:

    vector3 origin;

    virtual bool hit_ray(const Ray &ray, float t0, float t1, hit_record &rec) = 0;
    Surface(const vector3 &origin);
    Material *material;

    // TODO: bounding box
};