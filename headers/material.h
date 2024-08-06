#pragma once

#include "nikomath.h"

enum class MODEL {LAMBERT, BLINN_PHONG, AMBIENT};
class Material {
public:
    rgba diffuse_color;
    rgba specular_color = rgba(255, 255, 255);
    // How glossy the material is
    // 10 = eggshell, 100 = mildly shiny, 1000 = really glossy, 10'000 = nearly mirror like
    float phong_exponent; 
    MODEL model = MODEL::BLINN_PHONG;
    void set_model(MODEL model);
};