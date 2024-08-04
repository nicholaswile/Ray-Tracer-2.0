#pragma once

#include "scene.h"

class RayTracer {
public:
    void traceray(image &img, const Scene &scene);
};