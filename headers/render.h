#pragma once

#include "scene.h"

class RayTracer {
public:
    void traceray(image &img, const Scene &scene);
    rgba raycolor(const Ray *ray, float t0, float t1, const Scene &scene);
};