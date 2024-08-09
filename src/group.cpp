#include "../headers/group.h"

Group::Group() {}

bool Group::hit_ray(const Ray &ray, float t0, float t1, hit_record &rec)  const {
    bool hit = false;
    for (const auto &object : this->surfaces) {
        if (!object->hit_ray(ray, 0, t1, rec))
            continue;
        hit = true;
        t1 = rec.t;
        rec.mat = object->material;
    }
    return hit;
}

void Group::push_back(Surface *surface) {
    surfaces.push_back(surface);
}