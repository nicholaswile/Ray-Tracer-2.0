#pragma once

#include "nikomath.h"

enum class MODEL {LAMBERT, BLINN_PHONG, AMBIENT};
class Material {
public:
    rgba surface_color;
    MODEL model = MODEL::BLINN_PHONG;
    void set_model(MODEL model);
};