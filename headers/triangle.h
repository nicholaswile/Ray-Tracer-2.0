#pragma once

#include "surface.h"
#include <vector>

class Triangle : public Surface {
public:
    std::vector<vector3> verts;    
    Triangle(const vector3 &A, const vector3 &B, const vector3 &C);
    bool hit_ray(const Ray &ray, float t0, float t1, hit_record &rec) override;
};