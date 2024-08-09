#pragma once

#include "surface.h"
#include <vector>

// A group of surface objects
class Group : public Surface {
private:
    std::vector<Surface*> surfaces;
public:
    Group();
    void push_back(Surface *surface);
    bool hit_ray(const Ray &ray, float t0, float t1, hit_record &rec) const override;
};